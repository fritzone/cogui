#include "window.h"
#include "desktop.h"
#include "theme.h"

#include "log.h"

#include <memory>

cogui::window::OnResize::argument cogui::window::on_resize;
cogui::window::OnClose::argument cogui::window::on_close;
cogui::window::OnMouseDown::argument cogui::window::on_mouse_down;
cogui::window::OnMouseUp::argument cogui::window::on_mouse_up;
cogui::window::SystemMenu::argument cogui::window::sysmenu;
cogui::window::MenuBar::argument cogui::window::mainmenu;

cogui::window::~window()
{
    desktop::get().remove_window(this);
}

void cogui::window::draw() const
{
    auto t = cogui::desktop::get().getTheme();
    t->draw_window(*this);
    draw_content();
    if(m_current_menu)
    {
        t->draw_menu(*m_current_menu);
    }
    desktop::get().refresh();
}

void cogui::window::click(int x, int y)
{
   log_info() << "window click: x=" << x << " y=" << y << " sysmenu:" << m_sysmenu_btn_pos << " y=" << this->getY();

   //firstly: see if there is an open menu
   if(m_current_menu)
   {
       if(m_current_menu->inside(x, y))
       {
           auto tempm = m_current_menu;
           m_current_menu = nullptr;
           redraw();
           tempm->click(x, y);
       }
       else
       {
           // clicked outside the menu, close it
           m_current_menu->close();
           m_current_menu = nullptr;
           redraw();
       }
       return draw();
   }

   if(m_draw_state == draw_state::moving || m_draw_state == draw_state::resizing)
   {
       m_draw_state = draw_state::normal;
   }

   if(y == this->getY() && x == m_close_btn_pos)
   {
       // close click:
       // debug() << "click on close button";
       emit sig_on_close(this);
       return;
   }

   if(y == this->getY() && x == m_maximize_btn_pos)
   {
       // close click:
       // debug() << "click on close button";
       maximize();
       return;
   }

   // click on sysmenu?
   if(y == this->getY() && x == m_sysmenu_btn_pos)
   {
        log_info() << "click on sysmenu";
        m_current_menu = &m_sysmenu;
        m_current_menu->open(x - 1, y + 1);
        return draw();
   }

   // click on a menu from menubar
   if(hasMenubar())
   {

   }

   // did we click on a control by any chance?
   std::shared_ptr<control> under = element_under(x, y);
   if(under)
   {
       release_control(under);
       // debug() << "found under ontrol";
       under->click();
   }
   redraw();

}

void cogui::window::mouse_move(int x, int y)
{
    if(m_draw_state == draw_state::moving)
    {
        // debug() << "mouse moving at" <<x<<", "<<y;

        int new_x = x - m_mouse_down_x;
        int new_y = y - m_mouse_down_y;

        if(new_x >= 0 && new_y >= 0 && new_x + this->getWidth() < desktop::get().getWidth() - 1 && new_y + this->getHeight() < desktop::get().getHeight())
        {
            // debug() << "window moving at" <<x<<", "<<y;
            clear(); // clear is usually followed by a draw that why there is no refresh
            setX(new_x);
            setY(new_y);

            update_container();

            return draw();
        }
        else
        {
            // debug() << "window not moving at all at " <<x<<", "<<y;
        }
    }
    else
    if(m_draw_state == draw_state::resizing)
    {
        int dx = x - m_mouse_down_x - this->getX();
        int dy = y - m_mouse_down_y - this->getY();

        int attempted_new_width = m_prev_w + dx;
        if(attempted_new_width <= minimumDrawableWidth())
        {
            return;
        }

        if(getWidth() +  dx >= 5 && getHeight() + dy >= 5)
        {
            clear(); // clear is usually followed by a draw that why there is no refresh
            // log_info() << "w = " << getWidth() << " nw=" << getWidth() + dx;

            int temptative_width = m_prev_w + dx;
            int temptative_height = m_prev_h + dy;

            if(m_layout)
            {
                if(!m_layout->accept_new_size(m_tab_order, temptative_width, temptative_height))
                {
                    // return only if the new layout size is smaller than the current size
                    if(temptative_width < getWidth() && temptative_height < getHeight())
                    {
                        return draw();
                    }
                }
            }

            setWidth( m_prev_w + dx);
            setHeight( m_prev_h + dy);

            // if there is a layout attached
            reLayout(getWidth(), getHeight(), true);

            emit sig_on_resize(this, m_prev_w + dx, m_prev_h + dy);

            return draw();
        }
    }
    else
    {
        // do we have an opened menu? That takes priority over controls
        if(m_current_menu)
        {
            if(m_current_menu->inside(x, y))
            {
                if(m_current_menu->mouse_move(x, y))
                {
                    return draw();
                }
            }
            return;
        }
        // now go to the controls, see if the mouse is over of one of them or not
        std::shared_ptr<control> under = element_under(x, y);
        if(under)
        {

            //debug ()<< "got under element " << under;

            if(m_prev_pressed != m_tab_order.end() && !m_tab_order.empty())
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
        if(m_pressed != m_tab_order.end() && !m_tab_order.empty())
        {
            m_prev_pressed = m_pressed;

            (*m_pressed)->release();
            (*m_pressed)->unfocus();

            m_pressed = m_tab_order.end();
            m_focused = m_tab_order.end();

            return draw();
        }
    }

    // now if there was a control we have focused on, unfocus it since we moved outside of it
    if(m_focused != m_tab_order.end() && !m_tab_order.empty())
    {
        (*m_focused)->unfocus();
        return draw();
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
    log_info() << "This window was clicked:" << this;
}

int cogui::window::minimumDrawableWidth() const
{
    return desktop::get().getTheme()->minimum_window_width(*this);
}

int cogui::window::minimumDrawableHeight() const
{
    return desktop::get().getTheme()->minimum_window_height(*this);
}

void cogui::window::redraw()
{
    desktop::get().redraw();
}

void cogui::window::update_titlebar_btn_positions(int close_pos, int sysmenu_pos, int maximize_pos) const
{
    m_close_btn_pos = close_pos;
    m_sysmenu_btn_pos = sysmenu_pos;
    m_maximize_btn_pos = maximize_pos;
}

cogui::menu &cogui::window::getSystemMenu()
{
    return m_sysmenu;
}

const cogui::menu &cogui::window::getSystemMenu() const
{
    return m_sysmenu;
}

void cogui::window::closeCurrentMenu()
{
    m_current_menu->close();
    m_current_menu = nullptr;
}

const cogui::menubar &cogui::window::getMainMenu() const
{
    return m_mainmenu;
}

void cogui::window::left_mouse_down(int x, int y)
{
    // log_info() << "y=" << y << " topy=" << this->getY();
    if( y == this->getY() && x != m_close_btn_pos && x != m_sysmenu_btn_pos) // down on the top line, usually this means move the window
    {
        if(m_current_menu)
        {
            m_current_menu = nullptr;
            redraw();
        }

        // see: outside of sysmenu, maximize, close
        m_draw_state = draw_state::moving;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        return draw();
    }

    if(x == getWidth() + 1 + this->getX() && y == getHeight() + this->getY()) // in the lower right corner
    {
        if(m_current_menu)
        {
            m_current_menu = nullptr;
            redraw();
        }

        m_draw_state = draw_state::resizing;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        m_prev_w = getWidth();
        m_prev_h = getHeight();

        return draw();
    }

    // see if we have pressed the mouse on a control
    std::shared_ptr<control> under = element_under(x, y);
    if(under && !m_current_menu)
    {
        press_element(under);
        return draw();
    }

    // now if there was a control we have pressed the button on, release it since we clicked outside of it
    if(!m_tab_order.empty() && (m_prev_pressed != m_tab_order.end() || m_pressed != m_tab_order.end()) )
    {
        auto to_unpress_it = m_prev_pressed != m_tab_order.end() ? m_prev_pressed : m_pressed;
        release_control(*to_unpress_it);
        return draw();
    }

    // noone else captured this event, emit as a generic signal
    emit sig_on_mouse_down(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();
}

void cogui::window::left_mouse_up(int x, int y)
{
    log_info() << "UP: " << x << " " << y;
    m_draw_state = draw_state::normal;

    // now release the element if there was any pressed
    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        // see if the release has happened on the same control that was pressed on
        if(*m_prev_pressed == under)
        {
            release_control(under);
            // call the click
            under->click();
        }
        return draw();
    }

    // now if there was a control we have pressed the button on, release it
    if( !m_tab_order.empty() && (m_prev_pressed != m_tab_order.end() || m_pressed != m_tab_order.end()) )
    {
        auto to_unpress_it = m_prev_pressed != m_tab_order.end() ? m_prev_pressed : m_pressed;
        release_control(*to_unpress_it);
        return draw();
    }

    // nothing captured the left up, emit as signal
    emit sig_on_mouse_up(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();

}

void cogui::window::right_mouse_down(int x, int y)
{
    emit sig_on_mouse_down(this, cogui::mouse::button::right, x - this->getX(), y - this->getY());
}

void cogui::window::right_mouse_up(int x, int y)
{
    emit sig_on_mouse_up(this, cogui::mouse::button::right, x - this->getX(), y - this->getY());
}

void cogui::window::doubleclick(int x, int y)
{
    if(y == this->getY() && x != m_close_btn_pos && x != m_sysmenu_btn_pos) // down on the top line, usually this means move the window
    {
        maximize();
        return;
    }

    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        under->doubleclick();
    }
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

void cogui::window::maximize()
{

    if(m_window_state == window_state::normal)
    {
        m_initial_x = getX();
        m_initial_y = getY();
        m_initial_width = getWidth();
        m_initial_height = getHeight();

        setX(0);
        setY(0);
        setWidth(desktop::get().getWidth() - 2);
        setHeight(desktop::get().getHeight() - 1);

        m_window_state = window_state::maximized;

        reLayout();
    }
    else
    {
        desktop::get().clear();

        setX(m_initial_x);
        setY(m_initial_y);
        setWidth(m_initial_width);
        setHeight(m_initial_height);

        m_window_state = window_state::normal;

        reLayout();
    }

    redraw();
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
