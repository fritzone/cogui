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

    // now gather a list of all the windows that need to be repainted when this menu disappears

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

bool cogui::menu::mouse_move(int x, int y)
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
        return true;
    }
    return false;
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

int cogui::menu::getWidth() const
{
    return m_width;
}

cogui::action::~action()
{
    sig_on_trigger.disconnect(this, conn.get(), true);
}

cogui::action::action(const cogui::action &o)
{
    m_title = o.m_title;
    conn = o.conn;
    miso::connect(this, sig_on_trigger, conn.get());
}

cogui::action &cogui::action::operator=(const cogui::action &o)
{
    m_title = o.m_title;
    sig_on_trigger.disconnect(this, conn.get());
    sig_on_trigger = o.sig_on_trigger;
    conn = o.conn;
    miso::connect(this, sig_on_trigger, conn.get());
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
