#include "button.h"
#include "desktop.h"
#include "theme.h"

cogui::button::OnClick::argument cogui::button::on_click;

cogui::button::button(int x, int y, int width, int height, const std::wstring &title) : control(x, y, width, height, title)
{
}

void cogui::button::draw() const
{
    cogui::desktop::get().getTheme()->draw_button(*this);
}

void cogui::button::click()
{
    log_debug() << "Emitting a click signal";
    emit sig_on_click(this);
}

int cogui::button::minimumDrawableWidth() const
{
    return desktop::get().getTheme()->minimum_button_width(*this);
}

int cogui::button::minimumDrawableHeight() const
{
    return desktop::get().getTheme()->minimum_button_height(*this);
}
