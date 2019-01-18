#include "window.h"
#include "desktop.h"
#include "theme.h"

#include "loguru.h"

cogui::window::window(int x, int y, int w, int h): control(x, y, w, h),
    m_title(L"Very long title12")
{
    desktop::get().add_window(this);
}

cogui::window::~window()
{
    desktop::get().remove_window(this);
}

void cogui::window::draw() const
{
    cogui::desktop::get().theme()->draw_window(*this);
}

void cogui::window::click(int x, int y)
{
    LOG_S(INFO) << "window click: x=" << x << " y=" << y;
}

void cogui::window::mouse_move(int x, int y)
{

    info() << "x=" << x << " w=" << width() << " x()=" << this->x();
    info() << "y=" << y << " h=" << height()<< " y()=" << this->y();
    if(m_draw_state == draw_state::moving)
    {
        if(x - m_mouse_down_x >= 0 && y - m_mouse_down_y >= 0)
        {
            clear(); // clear is usually followed by a draw that why there is no refresh
            setX(x - m_mouse_down_x);
            setY(y - m_mouse_down_y);
            draw();
        }
    }

    if(m_draw_state == draw_state::resizing)
    {
        int dx = x - m_mouse_down_x - this->x();
        int dy = y - m_mouse_down_y - this->y();
        info() << "dx=" << dx << " dy=" << dy;
        if(width() +  dx >=5 && height() + dy>= 5)
        {
            clear(); // clear is usually followed by a draw that why there is no refresh
            info() << "w = " << width() << " nw=" << width() + dx;
            setWidth( m_prev_w + dx);
            setHeight( m_prev_h + dy);
            draw();
        }
    }
}

bool cogui::window::inside(int x, int y) const
{

    info() << "I x=" << x << " w=" << width() << " x()=" << this->x();
    info() << "I y=" << y << " h=" << height()<< " y()=" << this->y();

    return x >= this->x()
            && x <= this->x() + width() + 1
            && y >= this->y()
            && y <= this->y() + height()
            ;
}


void cogui::window::left_mouse_down(int x, int y)
{
    info() << "D x=" << x << " w=" << width() << " x()=" << this->x();
    info() << "D y=" << y << " h=" << height()<< " y()=" << this->y();
    if( y == this->y())
    {
        // see: outside of sysmenu, maximize, close
        m_draw_state = draw_state::moving;
        m_mouse_down_x = x - this->x();
        m_mouse_down_y = y - this->y();
        draw();
        return;
    }

    info() << "R x=" << x << " w=" << width();
    info() << "R y=" << y << " h=" << height();
    if(x == width() + 1 + this->x() && y == height() + this->y())
    {
        info() << "resize starts";
        m_draw_state = draw_state::resizing;
        m_mouse_down_x = x - this->x();
        m_mouse_down_y = y - this->y();
        m_prev_w = width();
        m_prev_h = height();

        draw();
        return;

    }
}

void cogui::window::left_mouse_up(int x, int y)
{
    info() << "UP: " << x << " " << y;
    m_draw_state = draw_state::normal;
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

std::wstring cogui::window::title() const
{
    return m_title;
}

void cogui::window::setTitle(const std::wstring &title)
{
    m_title = title;
}
