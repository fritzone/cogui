#include "mouse.h"

mouse &mouse::get()
{
    static mouse instance;
    return instance;
}

int mouse::x() const
{
    return m_x;
}

void mouse::setX(int x)
{
    m_x = x;
}

int mouse::y() const
{
    return m_y;
}

void mouse::setY(int y)
{
    m_y = y;
}

mouse::button mouse::buttons() const
{
    return m_button;
}

void mouse::set_button(mouse::button b)
{
    if(b == button::none) m_button = b;
    if(b == button::left)
    {
        if(m_button == button::right) m_button = button::left_and_right;
        else m_button = b;
    }
    if(b == button::right)
    {
        if(m_button == button::left) m_button = button::left_and_right;
        else m_button = b;
    }
}

void mouse::clear_button(mouse::button b)
{
    if(b == button::left)
    {
        if(m_button == button::left_and_right) m_button = button::right;
        else if(m_button == button::left) m_button = button::none;
    }
    if(b == button::right)
    {
        if(m_button == button::left_and_right) m_button = button::left;
        else if(m_button == button::right) m_button = button::none;
    }
}

mouse::mouse()
{

}
