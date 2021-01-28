#include "scrollbar.h"

cogui::scrollbar cogui::scrollbar::horizontal(cogui::scrollbar::orientation::so_horizontal);
cogui::scrollbar cogui::scrollbar::vertical(cogui::scrollbar::orientation::so_vertical);
cogui::scrollbar cogui::scrollbar::both(cogui::scrollbar::orientation::so_both);

cogui::scrollbar::scrollbar()
{
}

cogui::scrollbar::orientation cogui::scrollbar::get_orientation() const
{
    return m_orientation;
}

void cogui::scrollbar::set_orientation(cogui::scrollbar::orientation o)
{
    m_orientation = o;
}

void cogui::scrollbar::set_parent(cogui::control *c)
{
    m_parent = c;
}

cogui::control *cogui::scrollbar::get_parent() const
{
    return m_parent;
}

int cogui::scrollbar::get_handle_position() const
{
    return m_handle_position;
}

cogui::scrollbar::scrollbar(cogui::scrollbar::orientation o) : m_orientation(o)
{

}
