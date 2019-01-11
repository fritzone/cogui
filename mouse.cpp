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

mouse::mouse()
{

}
