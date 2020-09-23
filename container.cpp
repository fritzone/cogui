#include "container.h"

#include <algorithm>

std::map<const cogui::container*, std::vector<cogui::container::basic_store*>> cogui::container::m_container_stores;

cogui::container::container(int x, int y, int width, int height) : control(x, y, width, height)
{

}

cogui::button &cogui::container::add_button(int x, int y, int width, int height, const std::wstring &title)
{
    return *add_control<button>(x, y, width, height, this, title);
}

cogui::checkbox &cogui::container::add_checkbox(int x, int y, int width, int height, const std::wstring &title)
{
    return *add_control<checkbox>(x, y, width, height, this, title);
}

void cogui::container::draw_content() const
{
    const auto& cvs = m_container_stores[this];
    for(const auto& c : cvs)
    {
        c->draw();
    }
}

void cogui::container::update_container()
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

void cogui::container::focus_next_element()
{
    log_info() << "Focusing next element";
    if(m_focused == m_tab_order.end())
    {
        m_focused = m_tab_order.begin();
    }
    else
    {
        (*m_focused)->set_focus_state(cogui::control::focus_state::not_focused);
        ++m_focused;
        if(m_focused == m_tab_order.end())
        {
            m_focused = m_tab_order.begin();
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

void cogui::container::reLayout(int temptative_width, int temptative_height, bool force)
{
    if(m_layout)
    {
        if(m_layout->accept_new_size(m_tab_order, temptative_width, temptative_height) || force)
        {
            m_layout->arrange_controls(m_tab_order, this);
        }
    }
}

void cogui::container::reLayout()
{
    reLayout(getWidth(), getHeight(), true);
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
