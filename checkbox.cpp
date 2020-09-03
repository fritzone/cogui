#include "checkbox.h"
#include "desktop.h"
#include "theme.h"

cogui::checkbox::OnClick::argument cogui::checkbox::on_click;

cogui::checkbox::checkbox(int x, int y, int width, int height, const std::wstring &title) : control(x, y, width, height, title)
{
}

void cogui::checkbox::draw() const
{
    cogui::desktop::get().getTheme()->draw_checkbox(*this);
}

void cogui::checkbox::click()
{
    log_debug() << "Emitting a click signal";
    emit sig_on_click(this);
}

int cogui::checkbox::minimumDrawableWidth() const
{
    return desktop::get().getTheme()->minimum_checkbox_width(*this);
}

int cogui::checkbox::minimumDrawableHeight() const
{
    return desktop::get().getTheme()->minimum_checkbox_height(*this);
}

bool cogui::checkbox::checked() const
{
    return m_checked;
}
