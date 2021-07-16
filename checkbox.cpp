#include "checkbox.h"
#include "desktop.h"
#include "theme.h"

cogui::checkbox::OnClick::argument cogui::checkbox::on_click;
cogui::checkbox::OnStateChange::argument cogui::checkbox::on_state_change;
cogui::checkbox::CheckState::argument cogui::checkbox::checked;

void cogui::checkbox::click()
{
    m_checked = ! m_checked;
    emit sig_on_click(this);
    emit sig_on_state_change(this, m_checked);
	redraw();
}

void cogui::checkbox::set_checked(bool c)
{
    m_checked = c;
    emit sig_on_state_change(this, m_checked);
	redraw();
}

bool cogui::checkbox::is_checked() const
{
    return m_checked;
}

void cogui::checkbox::check()
{
    m_checked = true;
	emit sig_on_state_change(this, m_checked);
	redraw();
}

void cogui::checkbox::uncheck()
{
    m_checked = false;
	emit sig_on_state_change(this, m_checked);
	redraw();
}
