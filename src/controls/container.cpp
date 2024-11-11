#include "container.h"
#include <tuple>
#include <variant>
#include <algorithm>

std::map<const cogui::container*, std::vector<cogui::container::basic_store*>> cogui::container::m_container_stores;

cogui::container::container(int x, int y, int width, int height) : control(x, y, width, height)
{

}

void cogui::container::draw() const
{
    const auto& cvs = m_container_stores[this];
    for(const auto& c : cvs)
    {
        c->draw();
    }
}

void cogui::container::release_control(std::shared_ptr<cogui::control> c)
{
    // means, this is a click
    c->release();
    c->unfocus();

    // reset the controls
    m_prev_pressed = m_tab_order.end();
    m_pressed = m_tab_order.end();
    m_focused = m_tab_order.end();
}

std::vector<std::shared_ptr<cogui::control>>::iterator& cogui::container::focused()
{
    return m_focused;
}

int cogui::container::first_available_row() const
{
    return 1;
}

void cogui::container::focus_next_element()
{
    log_info() << "Focusing next element";
    if(m_focused == m_tab_order.end())
    {
        m_focused = m_tab_order.begin();
		while( m_focused != m_tab_order.end() && !(*m_focused)->is_visible()) ++m_focused;
		if(m_focused == m_tab_order.end())
		{
			return;
		}
	}
    else
    {
        (*m_focused)->set_focus_state(cogui::control::focus_state::not_focused);
		++m_focused;
		while( m_focused != m_tab_order.end() && !(*m_focused)->is_visible()) ++m_focused;
        if(m_focused == m_tab_order.end())
        {
            m_focused = m_tab_order.begin();
			while( m_focused != m_tab_order.end() && !(*m_focused)->is_visible()) ++m_focused;
			if(m_focused == m_tab_order.end())
			{
				return;
			}
        }
    }

    (*m_focused)->set_focus_state(cogui::control::focus_state::focused);

}

void cogui::container::focus_element(std::shared_ptr<cogui::control> c)
{
    if(m_focused != m_tab_order.end())
    {
        (*m_focused)->set_focus_state(cogui::control::focus_state::not_focused);
    }
    m_focused = std::find(m_tab_order.begin(), m_tab_order.end(), c);
    c->set_focus_state(cogui::control::focus_state::focused);
}

void cogui::container::press_element(std::shared_ptr<cogui::control> c)
{
    if(m_pressed != m_tab_order.end())
    {
        log_debug() << "releasing something";
        (*m_pressed)->release();
    }
    m_pressed = std::find(m_tab_order.begin(), m_tab_order.end(), c);

    if(m_pressed == m_tab_order.end())
    {
        log_warning() << "Pressed is still invalid";
    }
    c->press();

    m_prev_pressed = m_pressed;
}

void cogui::container::relayout(int temptative_width, int temptative_height, bool force)
{
    if(m_layout)
    {
        if(m_layout->accept_new_size(m_tab_order, temptative_width, temptative_height) || force)
        {
            m_layout->arrange_controls(m_tab_order, this);
        }
    }
}

void cogui::container::relayout()
{
	relayout(get_width(), get_height(), true);
}

std::shared_ptr<cogui::control> cogui::container::element_under(int x, int y)
{
    const auto& cvs = m_container_stores[this];
    for(const auto& c : cvs)
    {
        std::shared_ptr<control> u = c->element_under(x, y);
        if(u)
        {
            return u;
        }
    }

    return nullptr;
}
