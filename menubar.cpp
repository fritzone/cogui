#include "menubar.h"

cogui::menubar cogui::menubar::no_mainmenu;
cogui::menu cogui::menubar::align_right_after(L"::align_right_after", {});

bool cogui::menubar::operator ==(const cogui::menubar &oth) const
{
    return m_menus == oth.m_menus;
}

cogui::menubar::menubar(std::initializer_list<cogui::menu> entries) : m_menus(entries)
{
}

cogui::menubar &cogui::menubar::operator =(std::initializer_list<cogui::menu> m)
{
    m_menus = m;
    return *this;
}

const cogui::menu &cogui::menubar::operator[](int i) const
{
    if(i < static_cast<int>(m_menus.size()))
    {
        return m_menus[i];
    }
    throw "Index out of range";
}

const std::vector<cogui::menu> &cogui::menubar::items() const
{
    return m_menus;
}

std::vector<cogui::menu> &cogui::menubar::items()
{
    return m_menus;
}

cogui::menu *cogui::menubar::before(cogui::menu *m)
{
    auto it = find(m_menus.begin(), m_menus.end(), *m);

    if (it != m_menus.end())
    {
        int index = distance(m_menus.begin(), it);
        if(index == 0 && m_menus[m_menus.size() - 1].caption() != align_right_after.caption())
        {
            return &m_menus[m_menus.size() - 1] ;
        }
        while(index > 0 && m_menus[index - 1] == align_right_after)
        {
            index --;
        }
        if(index == 0)
        {
            return nullptr;
        }
        return &m_menus[index - 1];
    }
    return nullptr;
}

cogui::menu *cogui::menubar::after(cogui::menu *m)
{
    auto it = find(m_menus.begin(), m_menus.end(), *m);

    if (it != m_menus.end())
    {
        int index = distance(m_menus.begin(), it);
        if(index == static_cast<int>(m_menus.size()) - 1 && m_menus[0].caption() != align_right_after.caption())
        {
            return &m_menus[0] ;
        }
        while(index < static_cast<int>(m_menus.size()) - 1 && m_menus[index + 1] == align_right_after)
        {
            index ++;
        }
        if(index == static_cast<int>(m_menus.size() - 1))
        {
            return nullptr;
        }
        return &m_menus[index + 1];
    }
    return nullptr;
}


