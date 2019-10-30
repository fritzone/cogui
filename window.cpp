#include "window.h"
#include "desktop.h"
#include "theme.h"

#include "loguru.h"

#include <memory>

cogui::window::OnResize::argument cogui::window::on_resize;
cogui::window::OnClose::argument cogui::window::on_close;
cogui::window::OnMouseDown::argument cogui::window::on_mouse_down;
cogui::window::OnMouseUp::argument cogui::window::on_mouse_up;

cogui::window::window(int x, int y, int width, int height, const std::wstring &title):
    container(x, y, width, height, title)
{
    desktop::get().add_window(this);
}

cogui::window::window(int x, int y, int width, int height, const std::string &title):
    container(x, y, width, height, title)
{
    desktop::get().add_window(this);
}

cogui::window::~window()
{
    desktop::get().remove_window(this);
}

void cogui::window::draw() const
{
    cogui::desktop::get().getTheme()->draw_window(*this);
    draw_content();
    desktop::get().refresh();
}

void cogui::window::click(int x, int y)
{
   info() << "window click: x=" << x << " y=" << y;
   if(m_draw_state == draw_state::moving || m_draw_state == draw_state::resizing)
   {
       m_draw_state = draw_state::normal;
       return draw();
   }

   if(y == this->getY() && x == m_close_btn_pos)
   {
       // close click:
       debug() << "click on close button";
       emit sig_on_close(this);
       return;
   }

   // did we click on a control by any chance?
   std::shared_ptr<control> under = element_under(x, y);
   if(under)
   {
       debug() << "found under ontrol";
       under->click();
   }
}

void cogui::window::mouse_move(int x, int y)
{
    if(m_draw_state == draw_state::moving)
    {
        debug() << "mouse moving at" <<x<<", "<<y;
        if(x - m_mouse_down_x >= 0 && y - m_mouse_down_y >= 0)
        {
            debug() << "window moving at" <<x<<", "<<y;
            clear(); // clear is usually followed by a draw that why there is no refresh
            setX(x - m_mouse_down_x);
            setY(y - m_mouse_down_y);

            update_container();

            return draw();
        }
        else
        {
            debug() << "window not moving at all at " <<x<<", "<<y;
        }
    }
    else
    if(m_draw_state == draw_state::resizing)
    {
        int dx = x - m_mouse_down_x - this->getX();
        int dy = y - m_mouse_down_y - this->getY();
        if(getWidth() +  dx >=5 && getHeight() + dy>= 5)
        {
            clear(); // clear is usually followed by a draw that why there is no refresh
            info() << "w = " << getWidth() << " nw=" << getWidth() + dx;
            setWidth( m_prev_w + dx);
            setHeight( m_prev_h + dy);

            emit sig_on_resize(this, m_prev_w + dx, m_prev_h + dy);

            return draw();
        }
    }
    else
    {
        // now go to the controls, see if the mouse is over of one of them or not
        std::shared_ptr<control> under = element_under(x, y);
        if(under)
        {

            info()<< "got under element" << under;

            if(m_prev_pressed != m_tab_order.end())
            {
                if(under == *m_prev_pressed)
                {
                    m_pressed = m_prev_pressed;
                    (*m_pressed)->press();

                    return draw();
                }

            }
            else
            {
                focus_element(under);
                return draw();
            }
        }

        // here we do not have an element under the cursor, however if we had one
        // make sure to un-press it
        if(m_pressed != m_tab_order.end())
        {
            m_prev_pressed = m_pressed;

            (*m_pressed)->release();
            (*m_pressed)->unfocus();

            m_pressed = m_tab_order.end();
            m_focused = m_tab_order.end();

            return draw();
        }
    }
}

bool cogui::window::inside(int x, int y) const
{
    return x >= this->getX()
            && x <= this->getX() + getWidth() + 1
            && y >= this->getY()
            && y <= this->getY() + getHeight()
            ;
}

void cogui::window::click()
{
    info() << "This window was clicked:" << this;
}

void cogui::window::update_close_btn_pos(int nx) const
{
    m_close_btn_pos = nx;
    debug() << "Close at:" << m_close_btn_pos;
}


void cogui::window::left_mouse_down(int x, int y)
{
    info() << "y=" << y << " topy=" << this->getY();
    if( y == this->getY()) // down on the top line, usually this means move the window
    {
        // see: outside of sysmenu, maximize, close
        m_draw_state = draw_state::moving;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        return draw();
    }

    if(x == getWidth() + 1 + this->getX() && y == getHeight() + this->getY()) // in the lower right corner
    {
        m_draw_state = draw_state::resizing;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        m_prev_w = getWidth();
        m_prev_h = getHeight();

        return draw();
    }

    // see if we have pressed the mouse on a control
    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        debug() << "Under:" << under;
        press_element(under);
        return draw();
    }

    // noone else captured this event, emit as a generic signal

    emit sig_on_mouse_down(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();
}

void cogui::window::left_mouse_up(int x, int y)
{
    info() << "UP: " << x << " " << y;
    m_draw_state = draw_state::normal;

    // now release the element if there was any pressed
    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        debug() << "Release Under:" << under;
        // see if the release has happened on the same control that was pressed on
        if(*m_prev_pressed == under)
        {
            // means, this is a click
            under->release();
            under->unfocus();

            // call the click
            under->click();

            // reset the controls
            m_prev_pressed = m_tab_order.end();
            m_pressed = m_tab_order.end();
            m_focused = m_tab_order.end();
        }
        return draw();
    }

    // now if there was a control we have pressed the button on, release it
    if(m_prev_pressed != m_tab_order.end() || m_pressed != m_tab_order.end() )
    {
        auto to_unpress_it = m_prev_pressed != m_tab_order.end() ? m_prev_pressed : m_pressed;

        (*to_unpress_it)->release();

        // and remove the focus from it
        (*to_unpress_it)->unfocus();

        // reset the controls
        m_prev_pressed = m_tab_order.end();
        m_pressed = m_tab_order.end();
        m_focused = m_tab_order.end();

        return draw();
    }

    // nothing captured the left up, emit as signal
    emit sig_on_mouse_up(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();

}

bool cogui::window::hasSysmenuButton() const
{
    return m_hasSysmenuButton;
}

void cogui::window::setHasSysmenuButton(bool hasSysmenuButton)
{
    m_hasSysmenuButton = hasSysmenuButton;
}

cogui::window::draw_state cogui::window::getDrawState() const
{
    return m_draw_state;
}

bool cogui::window::hasMaximizeButton() const
{
    return m_hasMaximizeButton;
}

void cogui::window::setHasMaximizeButton(bool hasMaximizeButton)
{
    m_hasMaximizeButton = hasMaximizeButton;
}

bool cogui::window::hasCloseButton() const
{
    return m_hasCloseButton;
}

void cogui::window::setHasCloseButton(bool hasCloseButton)
{
    m_hasCloseButton = hasCloseButton;
}

bool cogui::window::resizeable() const
{
    return m_resizeable;
}

void cogui::window::setResizeable(bool resizeable)
{
    m_resizeable = resizeable;
}
