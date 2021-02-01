#include "action.h"

cogui::action::OnTrigger::argument cogui::action::on_trigger;
cogui::action::Selectable::argument cogui::action::selectable;

cogui::action::~action()
{
    sig_on_trigger.disconnect(this, m_conn.get(), true);
}

cogui::action::action(const cogui::action &o)
{
    *this = o;
    /*m_title = o.m_title;
    m_conn = o.m_conn;
    m_selectable = o.m_selectable;
    miso::connect(this, sig_on_trigger, m_conn.get());*/
}

cogui::action &cogui::action::operator=(const cogui::action &o)
{
    m_title = o.m_title;
    sig_on_trigger.disconnect(this, m_conn.get());
    sig_on_trigger = o.sig_on_trigger;
    m_conn = o.m_conn;
    m_selectable = o.m_selectable;
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
