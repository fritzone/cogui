#include "menu.h"
#include "menubar.h"
#include "utils.h"

#include <string>

cogui::action cogui::menu::separator_item(L"::separator_item");

cogui::menu::menu(std::initializer_list<cogui::action> l) : m_actions(l)
{
    register_action_activators();
}

cogui::menu::menu(const std::wstring &caption, std::initializer_list<cogui::action> l) : m_actions(l), m_is_sysmenu(false), m_caption(caption)
{
    register_action_activators();
}

cogui::menu::menu(const wchar_t * const caption, std::initializer_list<cogui::action> l) : menu(std::wstring(caption), l)
{
    register_action_activators();
}

cogui::menu::menu(const std::string &caption, std::initializer_list<cogui::action> l) : m_actions(l)
{
    m_caption = cogui::utils::std2ws(caption);
    m_is_sysmenu = false;
    register_action_activators();
}

void cogui::menu::append(std::initializer_list<cogui::action> l)
{
    m_actions.insert(m_actions.end(), l.begin(), l.end());
    register_action_activators();
}

cogui::menu &cogui::menu::operator =(std::initializer_list<cogui::action> l)
{
    m_actions = l;
    register_action_activators();
    return *this;
}

bool cogui::menu::operator ==(const cogui::menu &rhs) const
{
    return this->caption() == rhs.caption();
}

void cogui::menu::open(int x, int y)
{
    m_x = x;
    m_y = y;
    int max_len = 0;
    bool any_selectable = false;
    for(size_t i=0; i<m_actions.size(); i++)
    {
        if(m_actions[i].get_title() != cogui::menu::separator_item.get_title()
                && max_len < static_cast<int>(m_actions[i].get_title().length()))
        {
            max_len = m_actions[i].get_title().length();
        }

        if(m_actions[i].is_checkable())
        {
            any_selectable = true;
        }
    }

    m_width = max_len + 2;
    if(any_selectable)
    {
        m_width += 2;
    }

    m_height = m_actions.size() + 1;
    m_opened = true;
}

void cogui::menu::close()
{
    m_opened = false;
    m_lastSelectedIndex = -1;
}

int cogui::menu::getHeight() const
{
    return m_height;
}

bool cogui::menu::inside(int x, int y) const
{
    bool b = x > this->get_x() && x < this->get_x() + m_width && y > this->get_y() && y < this->get_y() + m_height;
    //debug() << "x=" << x <<" y=" << y << " this.x=" << this->getX() << " this.y=" << this->getY() << " this.w=" << this->getWidth() << " this.h=" << this->getHeight() << " in:" << b;
    return b;
}

bool cogui::menu::mouse_move(int, int y)
{
    if(m_lastSelectedIndex != y - get_y() - 1)
    {
        m_lastSelectedIndex = y - get_y() - 1;
        return true;
    }
    return false;
}

bool cogui::menu::click(int, int)
{
    // here we have clicked on the action at m_lastSelectedIndex
    if(m_lastSelectedIndex < static_cast<int>(m_actions.size()))
    {
        m_actions[m_lastSelectedIndex].trigger();
        m_opened = false;
        return true;
    }
    return false;
}

bool cogui::menu::keypress(std::shared_ptr<cogui::events::keypress> k)
{
    if(*k == cogui::events::key_class::key_up)
    {
        activate_previous_action();
        return true;

    }
    else
    if(*k == cogui::events::key_class::key_down)
    {
        activate_next_action();
        return true;
    }
    // Now let's see if this key is a hotkey key for and action in this menu this
	if(k->get_chardata().length() == 1)
	{
		for(auto& a : m_actions)
		{
			if(towupper(a.hotchar()) == towupper(k->get_chardata()[0]) )
			{
				a.trigger();
				m_opened = false;
				return true;
			}
		}
	}
    return false;
}

void cogui::menu::activate_action(size_t index)
{
    if(index < m_actions.size())
    {
        m_lastSelectedIndex = index;
    }
}

void cogui::menu::activate_next_action()
{
    int p = m_lastSelectedIndex;
    m_lastSelectedIndex ++;
    if(m_lastSelectedIndex == static_cast<int>(m_actions.size()))
    {
        m_lastSelectedIndex = 0;
    }

    while(m_actions[m_lastSelectedIndex].get_title() == separator_item.get_title())
    {
        m_lastSelectedIndex ++;
        if(m_lastSelectedIndex == static_cast<int>(m_actions.size()))
        {
            m_lastSelectedIndex = p;
            return;
        }
    }
}

void cogui::menu::activate_previous_action()
{
    int p = m_lastSelectedIndex;
    m_lastSelectedIndex --;

    if(m_lastSelectedIndex == -1)
    {
        m_lastSelectedIndex = m_actions.size() - 1;
    }

    // do not select separators while drawing the menu
    while(m_actions[m_lastSelectedIndex].get_title() == separator_item.get_title())
    {
        m_lastSelectedIndex --;
        if(m_lastSelectedIndex == -1)
        {
            m_lastSelectedIndex = p;
            return;
        }
    }
}

void cogui::menu::trigger_action(size_t index)
{

}

void cogui::menu::trigger_current_action()
{

}

bool cogui::menu::isOpened() const
{
    return m_opened;
}

const cogui::action &cogui::menu::operator[](int i) const
{
    if(i < static_cast<int>(m_actions.size()) && i >= 0)
    {
        return m_actions[i];
    }

    throw "Index out of size";
}

int cogui::menu::getLastSelectedIndex() const
{
    return m_lastSelectedIndex;
}

bool cogui::menu::isSysmenu() const
{
    return m_is_sysmenu;
}

std::wstring cogui::menu::caption() const
{
    return m_caption;
}

int cogui::menu::get_action_count() const
{
    return m_actions.size();
}

bool cogui::menu::is_right_align_specifier() const
{
    return caption() == cogui::menubar::align_right_after.caption();
}

void cogui::menu::register_action_activators()
{
    for(size_t i = 0; i < m_actions.size(); i++)
    {
        auto& a = const_cast<cogui::action&>(m_actions[i]);
        std::wstring caption = a.get_title();
        auto andp = caption.find(L"&");
        if(andp != std::string::npos && andp < caption.length() - 1)
        {
            std::wstring keydata;
            keydata += (wchar_t)caption[andp + 1];
            log_info() << "Hotkey found for action" << caption << "as:" << keydata;
            cogui::events::keypress* hk = new cogui::events::keypress(cogui::events::key_class::key_textinput, false, false, false, keydata);
            std::shared_ptr<cogui::events::keypress> sp;
            sp.reset(hk);
            sp->set_as_hotkey();
            m_action_activators[sp] = &m_actions[i];
        }
    }
}

int cogui::menu::getWidth() const
{
    return m_width;
}
