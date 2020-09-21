#include "menu.h"
#include <codecvt>
#include <string>
#include <locale>

cogui::action::OnTrigger::argument cogui::action::on_trigger;
cogui::action::Selectable cogui::action::selectable;
cogui::menubar cogui::menubar::no_mainmenu;
cogui::menu cogui::menubar::align_right_after(L"::align_right_after", {});
cogui::action cogui::menu::separator_item(L"::separator_item");

cogui::menu::menu(std::initializer_list<cogui::action> l) : m_actions(l)
{
}

cogui::menu::menu(const std::wstring &caption, std::initializer_list<cogui::action> l) : m_actions(l), m_is_sysmenu(false), m_caption(caption)
{
}

cogui::menu::menu(const wchar_t * const caption, std::initializer_list<cogui::action> l) : menu(std::wstring(caption), l){}

cogui::menu::menu(const std::string &caption, std::initializer_list<cogui::action> l) : m_actions(l)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    m_caption = converter.from_bytes(caption);
    m_is_sysmenu = false;
}

void cogui::menu::append(std::initializer_list<cogui::action> l) {
    m_actions.insert(m_actions.end(), l.begin(), l.end());
}

cogui::menu &cogui::menu::operator =(std::initializer_list<cogui::action> l)
{
    m_actions = l;
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
        if(m_actions[i].getTitle() != cogui::menu::separator_item.getTitle()
                && max_len < static_cast<int>(m_actions[i].getTitle().length()))
        {
            max_len = m_actions[i].getTitle().length();
        }

        if(m_actions[i].isSelectable())
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

    // now gather a list of all the windows that need to be repainted when this menu disappears

}

void cogui::menu::close()
{
    m_opened = false;
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

bool cogui::menu::inside(int x, int y) const
{
    bool b = x > this->getX() && x < this->getX() + m_width && y > this->getY() && y < this->getY() + m_height;
    //debug() << "x=" << x <<" y=" << y << " this.x=" << this->getX() << " this.y=" << this->getY() << " this.w=" << this->getWidth() << " this.h=" << this->getHeight() << " in:" << b;
    return b;
}

bool cogui::menu::mouse_move(int, int y)
{
    if(m_lastSelectedIndex != y - getY() - 1)
    {
        m_lastSelectedIndex = y - getY() - 1;
        return true;
    }
    return false;
}

bool cogui::menu::click(int, int)
{
    // here we have clicked on the action at m_lastSelectedIndex
    if(m_lastSelectedIndex < m_actions.size())
    {
        m_actions[m_lastSelectedIndex].trigger();
        m_opened = false;
        return true;
    }
    return false;
}

bool cogui::menu::isOpened() const
{
    return m_opened;
}

const cogui::action &cogui::menu::operator[](int i) const
{
    if(i < m_actions.size())
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

int cogui::menu::getWidth() const
{
    return m_width;
}

cogui::action::~action()
{
    sig_on_trigger.disconnect(this, m_conn.get(), true);
}

cogui::action::action(const cogui::action &o)
{
    m_title = o.m_title;
    m_conn = o.m_conn;
    miso::connect(this, sig_on_trigger, m_conn.get());
}

cogui::action &cogui::action::operator=(const cogui::action &o)
{
    m_title = o.m_title;
    sig_on_trigger.disconnect(this, m_conn.get());
    sig_on_trigger = o.sig_on_trigger;
    m_conn = o.m_conn;
    miso::connect(this, sig_on_trigger, m_conn.get());

    return *this;
}

void cogui::action::trigger()
{
    emit sig_on_trigger(this);
}

std::wstring cogui::action::getTitle() const
{
    return m_title;
}

void cogui::action::setTitle(const std::wstring &title)
{
    m_title = title;
}

bool cogui::action::isSelectable() const
{
    return m_selectable;
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
    if(i < m_menus.size())
    {
        return m_menus[i];
    }
    throw "Index out of range";
}

const std::vector<cogui::menu> &cogui::menubar::items() const
{
    return m_menus;
}
