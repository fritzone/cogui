#include "control.h"
#include "log.h"
#include "desktop.h"
#include "theme.h"

#include <string>

void cogui::control::initInitialPosition()
{
    m_initial_x = m_x;
    m_initial_y = m_y;
    m_initial_width = m_width;
    m_initial_height = m_height;
}

cogui::control::control(int x, int y, int w, int h) : m_x(x), m_y(y), m_width(w), m_height(h)
{
    log_info() << "Created a control at:" << x << ", " << y;
    initInitialPosition();
}

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

int cogui::control::getHeight() const
{
    return m_height;
}

void cogui::control::setHeight(int h)
{
    m_height = h;
}

bool cogui::control::inside(int x, int y) const
{
    return x >= this->getX() && x < this->getX() + m_width && y >= this->getY() && y < this->getY() + m_height;
}

void cogui::control::clear() const
{
    cogui::desktop::get().getTheme()->clear(*this);
}

cogui::control *cogui::control::getParent() const
{
    return m_parent;
}

void cogui::control::setParent(cogui::control *value)
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

void cogui::control::redraw()
{
    clear();
    draw();
}

void cogui::control::doubleclick()
{
    log_info() << "Double click, ignored for this control";
}

int cogui::control::getWidth() const
{
    return m_width;
}

void cogui::control::setWidth(int w)
{
    m_width = w;
}

int cogui::control::getY() const
{
    return m_parent ? m_parent->getY() + m_y : m_y;
}

void cogui::control::setY(int y)
{
    log_debug() << "set y=" << y << " to" << (char*)m_title.c_str();
    m_y = y;
}

int cogui::control::getX() const
{
    return m_parent ? m_parent->getX() + m_x : m_x;
}

void cogui::control::setX(int x)
{
    m_x = x;
}

std::wstring cogui::control::getTitle() const
{
    return m_title;
}

void cogui::control::setTitle(const std::wstring &title)
{
    m_title = title;
    redraw();
}
