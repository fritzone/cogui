#include "control.h"
#include "desktop.h"
#include "theme.h"

cogui::control::control(int x, int y, int w, int h) : m_x(x), m_y(y), m_w(w), m_h(h)
{
}

int cogui::control::height() const
{
    return m_h;
}

void cogui::control::setHeight(int h)
{
    m_h = h;
}

bool cogui::control::inside(int x, int y) const
{
    return x >= m_x && x < m_x + m_w && y >= m_y && y < m_y + m_h;
}

void cogui::control::clear() const
{
    cogui::desktop::get().theme()->clear(*this);
}

int cogui::control::width() const
{
    return m_w;
}

void cogui::control::setWidth(int w)
{
    m_w = w;
}

int cogui::control::y() const
{
    return m_y;
}

void cogui::control::setY(int y)
{
    m_y = y;
}

int cogui::control::x() const
{
    return m_x;
}

void cogui::control::setX(int x)
{
    m_x = x;
}
