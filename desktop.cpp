#include "desktop.h"
#include "graphics.h"
#include "theme.h"
#include "window.h"

#include <algorithm>
#define LOGURU_WITH_STREAMS 1

#include "loguru.h"

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

void desktop::handle_mouse_left_click(int x, int y)
{
    for(auto w : m_windows)
    {
        if(w->inside(x, y))
        {
            LOG_S(INFO) << "inside";
            w->click( x - w->x(), y - w->y() );
        }
    }
}

void desktop::handle_mouse_left_down(int x, int y)
{
    for(auto w : m_windows)
    {
        if(w->inside(x, y))
        {
            LOG_S(INFO) << "inside";
            w->left_mouse_down( x - w->x(), y - w->y() );
        }
    }

}

std::shared_ptr<cogui::theme> desktop::theme() const
{
    return m_theme;
}

std::shared_ptr<graphics> desktop::graphics() const
{
    return m_graphics;
}

void desktop::add_window(window *w)
{
    m_windows.push_back(w);
}

void desktop::remove_window(window *w)
{
    m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), w), m_windows.end());
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
