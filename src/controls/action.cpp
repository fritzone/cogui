#include "action.h"

#include <menu.h>

cogui::action::OnTrigger::argument cogui::action::on_trigger;
cogui::action::Checkable::argument cogui::action::checkable;
cogui::action::Checked::argument cogui::action::checked;

cogui::action::~action()
{
    if(!is_separator())
    {
        log_info() << "Disconnecting:" << m_title;
        sig_on_trigger.disconnect(this, m_conn.get(), true);
    }
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
	determine_hotchar();
    return *this;
}

void cogui::action::trigger()
{
	check();
	emit sig_on_trigger(this);
}

void cogui::action::check()
{
	if(is_checkable())
	{
		m_checked = !m_checked;
	}
}

std::wstring cogui::action::get_title() const
{
    return m_title;
}

void cogui::action::set_title(const std::wstring &title)
{
    m_title = title;
	determine_hotchar();
}

bool cogui::action::is_checkable() const
{
    return m_checkable;
}

bool cogui::action::is_checked() const
{
	return m_checked;
}

wchar_t cogui::action::hotchar() const
{
	return m_hotchar;
}

bool cogui::action::is_separator() const
{
    return get_title() == cogui::menu::separator_item.get_title();
}

void cogui::action::determine_hotchar()
{
	for(std::size_t i=0; i<m_title.length(); i++)
	{
		if(m_title[i] == L'&')
		{
			i++;
			if( i< m_title.length() )
			{
				if( m_title[i] != L'&')
				{
					m_hotchar = m_title[i];
					break;
				}
			}
		}
	}
}
