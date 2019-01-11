#include "desktop.h"
#include "graphics.h"
#include "theme.h"

namespace cogui
{

bool desktop::initialize()
{
    return m_graphics->initialize();
}

bool desktop::set_chars(int x, int y, const std::wstring &s)
{
    return m_graphics->set_chars(x, y, s);
}

void desktop::handle_mouse_left_click()
{

}

std::shared_ptr<cogui::theme> desktop::theme() const
{
    return m_theme;
}

std::shared_ptr<graphics> desktop::graphics() const
{
    return m_graphics;
}

desktop &desktop::get()
{
    static desktop a;
    static bool desk_init = a.initialize();
    return a;
}

desktop::desktop() : m_graphics(new cogui::graphics), m_theme(new cogui::theme)
{
}

}
