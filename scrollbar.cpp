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

void cogui::scrollbar::recalculate_step()
{
    if(m_dec_pos_set && m_inc_pos_set)
    {
        m_dec_pos_set = m_inc_pos_set = false;
        if(m_orientation == orientation::so_horizontal)
        {
            m_dist = (m_inc_arrow_screen_position.x - m_dec_arrow_screen_position.x - m_inc_arrow_screen_position.width - m_dec_arrow_screen_position.width);
            m_step = static_cast<float>(m_max_value - m_min_value) / static_cast<float>(m_dist);
        }
        else
        if(m_orientation == orientation::so_vertical)
        {
            m_dist = (m_inc_arrow_screen_position.y - m_dec_arrow_screen_position.y - m_inc_arrow_screen_position.height - m_dec_arrow_screen_position.height);
            m_step = static_cast<float>(m_max_value - m_min_value) / static_cast<float>(m_dist);
        }
    }
}

void cogui::scrollbar::set_handle_screen_position(const rect &handle_screen_position)
{
    m_handle_screen_position = handle_screen_position;
}

void cogui::scrollbar::set_value(int v)
{
    m_current_value = v;
}

int cogui::scrollbar::get_value() const
{
    return m_current_value;
}

void cogui::scrollbar::step_up()
{
    m_current_value += m_step;
    if(m_current_value >= m_max_value)
    {
        m_current_value = m_max_value - 1;
    }
    set_handle_position(m_current_value / m_step);
    debug_me();
}

void cogui::scrollbar::step_down()
{
    m_current_value -= m_step;
    if(m_current_value < m_min_value)
    {
        m_current_value = m_min_value;
    }
    set_handle_position(m_current_value / m_step);
    debug_me();

}

void cogui::scrollbar::step_to_location(int locationx, int locationy)
{
    if(m_orientation == orientation::so_horizontal)
    {
        // use locationx
        m_current_value = m_max_value - static_cast<int>((static_cast<float>( (m_inc_arrow_screen_position.x - m_inc_arrow_screen_position.width - locationx)  * (m_max_value - m_min_value) ) /
                static_cast<float>( m_inc_arrow_screen_position.x - m_inc_arrow_screen_position.width - m_dec_arrow_screen_position.x - m_dec_arrow_screen_position.width)));

        if(m_current_value > m_max_value) m_current_value = m_max_value;
        if(m_current_value < m_min_value) m_current_value = m_min_value;

        set_handle_position(m_current_value / m_step);
        debug_me();
    }

    if(m_orientation == orientation::so_vertical)
    {
        // use locationy
        m_current_value = m_max_value - static_cast<int>((static_cast<float>( (m_inc_arrow_screen_position.y - m_inc_arrow_screen_position.height - locationy)  * (m_max_value - m_min_value) ) /
                static_cast<float>( m_inc_arrow_screen_position.y - m_inc_arrow_screen_position.height - m_dec_arrow_screen_position.y - m_dec_arrow_screen_position.height)));

        if(m_current_value > m_max_value) m_current_value = m_max_value;
        if(m_current_value < m_min_value) m_current_value = m_min_value;

        set_handle_position(m_current_value / m_step);
        debug_me();
    }

}

void cogui::scrollbar::set_handle_position(int h)
{
    if(h < m_dist)
    {
        m_handle_position = h;
    }
    else
    {
        m_handle_position = m_dist;
    }
}

void cogui::scrollbar::debug_me()
{
    log_debug() << "scrollbar: m_step = "  << m_step << " current:" << m_current_value << " dist:" << m_dist << " handle:" << m_handle_position;
}

void cogui::scrollbar::set_inc_arrow_screen_position(const rect &inc_arrow_screen_position)
{
    m_inc_arrow_screen_position = inc_arrow_screen_position;
    m_inc_pos_set = true;
    recalculate_step();
}

void cogui::scrollbar::set_dec_arrow_screen_position(const rect &dec_arrow_screen_position)
{
    m_dec_arrow_screen_position = dec_arrow_screen_position;
    m_dec_pos_set = true;
    recalculate_step();
}
