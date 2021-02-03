#include "action.h"

cogui::action::OnTrigger::argument cogui::action::on_trigger;
cogui::action::Checkable::argument cogui::action::checkable;
cogui::action::Checked::argument cogui::action::checked;

cogui::action::~action()
{
    sig_on_trigger.disconnect(this, m_conn.get(), true);
}

cogui::action::action(const cogui::action &o)
{
    *this = o;
}

cogui::action &cogui::action::operator=(const cogui::action &o)
{
    m_title = o.m_title;
    sig_on_trigger.disconnect(this, m_conn.get());
    sig_on_trigger = o.sig_on_trigger;
    m_conn = o.m_conn;
    m_checkable = o.m_checkable;
    miso::connect(this, sig_on_trigger, m_conn.get());

    return *this;
}

void cogui::action::trigger()
{
    if(is_checkable())
    {
        m_checked = !m_checked;
    }

    emit sig_on_trigger(this);
}

std::wstring cogui::action::get_title() const
{
    return m_title;
}

void cogui::action::set_title(const std::wstring &title)
{
    m_title = title;
}

bool cogui::action::is_checkable() const
{
    return m_checkable;
}

bool cogui::action::is_checked() const
{
    return m_checked;
}
