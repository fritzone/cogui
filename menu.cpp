#include "menu.h"

cogui::action::OnTrigger::argument cogui::action::on_trigger;

cogui::menu::menu(std::initializer_list<cogui::action> l) : m_actions(l)
{

}

void cogui::menu::append(std::initializer_list<cogui::action> l) {
    m_actions.insert(m_actions.end(), l.begin(), l.end());
}

cogui::menu &cogui::menu::operator =(std::initializer_list<cogui::action> l)
{
    m_actions = l;
    return *this;
}

void cogui::menu::open(int x, int y)
{
    m_x = x;
    m_y = y;
    int max_len = 0;
    for(int i=0; i<m_actions.size(); i++)
    {
        if(max_len < m_actions[i].getTitle().length())
        {
            max_len = m_actions[i].getTitle().length();
        }
    }
    m_width = max_len + 2;
    m_height = m_actions.size() + 1;
}

int cogui::menu::getX() const
{
    return m_x;
}

int cogui::menu::getY() const
{
    return m_y;
}

int cogui::menu::getHeight() const
{
    return m_height;
}

const cogui::action &cogui::menu::operator[](int i) const
{
    if(i < m_actions.size())
    {
        return m_actions[i];
    }

    throw "Index out of size";
}

int cogui::menu::getWidth() const
{
    return m_width;
}

std::wstring cogui::action::getTitle() const
{
    return m_title;
}

void cogui::action::setTitle(const std::wstring &title)
{
    m_title = title;
}
