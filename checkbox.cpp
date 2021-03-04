#include "checkbox.h"
#include "desktop.h"
#include "theme.h"

cogui::checkbox::OnClick::argument cogui::checkbox::on_click;
cogui::checkbox::OnStateChange::argument cogui::checkbox::on_state_change;

cogui::checkbox::checkbox(int x, int y, int width, int height, const std::wstring &title) : control(x, y, width, height, title)
{
}

void cogui::checkbox::draw() const
{
    cogui::desktop::get().getTheme()->draw_checkbox(*this);
}

void cogui::checkbox::click()
{
    m_checked = ! m_checked;
    emit sig_on_click(this);
    emit sig_on_state_change(this, m_checked);

    cogui::desktop::get().redraw();
}

int cogui::checkbox::minimum_drawable_width() const
{
    return desktop::get().getTheme()->minimum_checkbox_width(*this);
}

int cogui::checkbox::minimum_drawable_height() const
{
    return desktop::get().getTheme()->minimum_checkbox_height(*this);
}

void cogui::checkbox::setChecked(bool c)
{
    m_checked = c;
    redraw();
    emit sig_on_state_change(this, m_checked);
}

bool cogui::checkbox::checked() const
{
    return m_checked;
}

void cogui::checkbox::check()
{
    m_checked = true;
    redraw();
}

void cogui::checkbox::uncheck()
{
    m_checked = false;
    redraw();
}
