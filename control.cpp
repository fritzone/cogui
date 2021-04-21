#include "control.h"
#include "log.h"
#include "desktop.h"
#include "theme.h"
#include "scrollbar.h"

#include <string>

cogui::control::control(int x, int y, int w, int h) : m_x(x), m_y(y), m_width(w), m_height(h)
{
    log_info() << "Created a control at:" << x << ", " << y;

    m_initial_x = m_x;
    m_initial_y = m_y;
    m_initial_width = m_width;
    m_initial_height = m_height;}

cogui::control::control(int x, int y, int width, int height, const std::wstring &title):
    cogui::control::control(x, y, width, height)
{
    m_title = title;
}

cogui::control::control(int x, int y, int width, int height, const std::string &title) :
    cogui::control::control(x, y, width, height)
{
    m_title = cogui::utils::std2ws(title);
}

int cogui::control::get_height() const
{
    return m_height;
}

void cogui::control::set_height(int h)
{
    m_height = h;
}

bool cogui::control::inside(int x, int y) const
{
    return x >= this->get_x() && x < this->get_x() + m_width && y >= this->get_y() && y < this->get_y() + m_height;
}

std::shared_ptr<cogui::scrollbar> cogui::control::mouse_down_on_scrollbar_decrease(int x, int y)
{
    if(m_horizontal_scrollbar && (x >= m_horizontal_scrollbar->m_dec_arrow_screen_position.x && y >=  m_horizontal_scrollbar->m_dec_arrow_screen_position.y &&
            x < m_horizontal_scrollbar->m_dec_arrow_screen_position.x + m_horizontal_scrollbar->m_dec_arrow_screen_position.width &&
            y < m_horizontal_scrollbar->m_dec_arrow_screen_position.y + m_horizontal_scrollbar->m_dec_arrow_screen_position.height))
    {
        return m_horizontal_scrollbar;
    }
    if(m_vertical_scrollbar && (x >= m_vertical_scrollbar->m_dec_arrow_screen_position.x && y >=  m_vertical_scrollbar->m_dec_arrow_screen_position.y &&
            x < m_vertical_scrollbar->m_dec_arrow_screen_position.x + m_vertical_scrollbar->m_dec_arrow_screen_position.width &&
            y < m_vertical_scrollbar->m_dec_arrow_screen_position.y + m_vertical_scrollbar->m_dec_arrow_screen_position.height))
    {
        return m_vertical_scrollbar;
    }

    return nullptr;
}

std::shared_ptr<cogui::scrollbar> cogui::control::mouse_down_on_scrollbar_increase(int x, int y)
{
    if(m_horizontal_scrollbar && (x >= m_horizontal_scrollbar->m_inc_arrow_screen_position.x && y >=  m_horizontal_scrollbar->m_inc_arrow_screen_position.y &&
            x < m_horizontal_scrollbar->m_inc_arrow_screen_position.x + m_horizontal_scrollbar->m_inc_arrow_screen_position.width &&
            y < m_horizontal_scrollbar->m_inc_arrow_screen_position.y + m_horizontal_scrollbar->m_inc_arrow_screen_position.height))
    {
        return m_horizontal_scrollbar;
    }
    if(m_vertical_scrollbar && (x >= m_vertical_scrollbar->m_inc_arrow_screen_position.x && y >=  m_vertical_scrollbar->m_inc_arrow_screen_position.y &&
            x < m_vertical_scrollbar->m_inc_arrow_screen_position.x + m_vertical_scrollbar->m_inc_arrow_screen_position.width &&
            y < m_vertical_scrollbar->m_inc_arrow_screen_position.y + m_vertical_scrollbar->m_inc_arrow_screen_position.height))
    {
        return m_vertical_scrollbar;
    }

    return nullptr;
}

std::shared_ptr<cogui::scrollbar> cogui::control::mouse_down_on_scrollbar_midportion(int x, int y)
{

    if(m_horizontal_scrollbar)
    {
        if(x >= m_horizontal_scrollbar->m_dec_arrow_screen_position.x + m_horizontal_scrollbar->m_dec_arrow_screen_position.width )
        {
            if(x < m_horizontal_scrollbar->m_inc_arrow_screen_position.x)
            {
                if(y >=  m_horizontal_scrollbar->m_inc_arrow_screen_position.y )
                {
                    if(y < m_horizontal_scrollbar->m_inc_arrow_screen_position.y + m_horizontal_scrollbar->m_inc_arrow_screen_position.height)
                    {
                        if( (x < m_horizontal_scrollbar->m_handle_screen_position.x || x > m_horizontal_scrollbar->m_handle_screen_position.x + m_horizontal_scrollbar->m_handle_screen_position.width))
                        {
                            return m_horizontal_scrollbar;

                        }
                    }
                }
            }
        }
    }

    if(m_vertical_scrollbar)
    {
        if(y >= m_vertical_scrollbar->m_dec_arrow_screen_position.y + m_vertical_scrollbar->m_dec_arrow_screen_position.height )
        {
            if(y < m_vertical_scrollbar->m_inc_arrow_screen_position.y)
            {
                if(x >=  m_vertical_scrollbar->m_inc_arrow_screen_position.x )
                {
                    if(x < m_vertical_scrollbar->m_inc_arrow_screen_position.x + m_vertical_scrollbar->m_inc_arrow_screen_position.width)
                    {
                        if( (y < m_vertical_scrollbar->m_handle_screen_position.y || y > m_vertical_scrollbar->m_handle_screen_position.y + m_vertical_scrollbar->m_handle_screen_position.height))
                        {
                            return m_vertical_scrollbar;
                        }
                    }
                }
            }
        }

    }


    return nullptr;

}

bool cogui::control::deal_with_scrollbar_mouse_down(int x, int y)
{
    auto decreasing_scrollbar = mouse_down_on_scrollbar_decrease(x, y);
    if(decreasing_scrollbar)
    {
        decreasing_scrollbar->step_down();
        return true;
    }

    auto incsing_scrollbar = mouse_down_on_scrollbar_increase(x, y);
    if(incsing_scrollbar)
    {
        incsing_scrollbar->step_up();
        return true;
    }

    auto midclicked_scrollbar = mouse_down_on_scrollbar_midportion(x, y);
    if(midclicked_scrollbar)
    {
        midclicked_scrollbar->step_to_location(x, y);
        return true;
    }

    return false;

}

void cogui::control::clear() const
{
    cogui::desktop::get().getTheme()->clear(*this);
}

cogui::control *cogui::control::get_parent() const
{
    return m_parent;
}

void cogui::control::set_parent(cogui::control *value)
{
    m_parent = value;
}

void cogui::control::focus()
{
    m_focus_state = focus_state::focused;
}

void cogui::control::unfocus()
{
    m_focus_state = focus_state::not_focused;
}

cogui::control::focus_state cogui::control::get_focus_state() const
{
    return m_focus_state;
}

bool cogui::control::has_focus() const
{
    return m_focus_state == focus_state::focused;
}

void cogui::control::show()
{
    m_visible = true;
}

void cogui::control::hide()
{
    m_visible = false;
}

bool cogui::control::is_visible() const
{
    return m_visible ;
}

void cogui::control::control::set_focus_state(const cogui::control::focus_state &focus_state)
{
    m_focus_state = focus_state;
}

void cogui::control::press()
{
    m_state = press_state::pressed;
}

void cogui::control::release()
{
    m_state = press_state::released;
}

bool cogui::control::is_pressed() const
{
    return m_state == press_state::pressed;
}

cogui::control::press_state cogui::control::get_press_state() const
{
    return m_state;
}

void cogui::control::set_press_state(cogui::control::press_state s)
{
    m_state = s;
}

const cogui::scrollbar &cogui::control::get_horizontal_scrollbar() const
{
    return *m_horizontal_scrollbar;
}

const cogui::scrollbar &cogui::control::get_vertical_scrollbar() const
{
    return *m_vertical_scrollbar;
}

void cogui::control::redraw()
{
    clear();
    draw();
}

void cogui::control::doubleclick(int, int)
{
    log_info() << "Double click, ignored for this control";
}

int cogui::control::get_width() const
{
    return m_width;
}

void cogui::control::set_width(int w)
{
    m_width = w;
}

int cogui::control::get_y() const
{
    return m_parent ? m_parent->get_y() + m_y : m_y;
}

void cogui::control::set_y(int y)
{
    log_debug() << "set y=" << y << " to" << (char*)m_title.c_str();
    m_y = y;
}

void cogui::control::set_bounds(int x, int y, int w, int h)
{
    set_x(x);
    set_y(y);
    set_width(w);
    set_height(h);
}

int cogui::control::get_x() const
{
    return m_parent ? m_parent->get_x() + m_x : m_x;
}

void cogui::control::set_x(int x)
{
    m_x = x;
}

std::wstring cogui::control::get_title() const
{
    return m_title;
}

void cogui::control::set_title(const std::wstring &title)
{
    m_title = title;
    redraw();
}
