#include "window.h"
#include "desktop.h"
#include "theme.h"

#include "loguru.h"

cogui::window::window(int x, int y, int w, int h): control(x, y, w, h),
    m_title(L"Very long title12")
{
    desktop::get().add_window(this);
}

cogui::window::~window()
{
    desktop::get().remove_window(this);
}

void cogui::window::draw() const
{
    cogui::desktop::get().theme()->draw_window(*this);
}

void cogui::window::click(int x, int y)
{
    LOG_S(INFO) << "window click: x=" << x << " y=" << y;
}

void cogui::window::left_mouse_down(int x, int y)
{
    if( y == 0)
    {
        // see: outside of sysmenu, maximize, close
        m_draw_state = draw_state::resizing;
        draw();
    }
}

bool cogui::window::hasSysmenuButton() const
{
    return m_hasSysmenuButton;
}

void cogui::window::setHasSysmenuButton(bool hasSysmenuButton)
{
    m_hasSysmenuButton = hasSysmenuButton;
}

cogui::window::draw_state cogui::window::getDrawState() const
{
    return m_draw_state;
}

bool cogui::window::hasMaximizeButton() const
{
    return m_hasMaximizeButton;
}

void cogui::window::setHasMaximizeButton(bool hasMaximizeButton)
{
    m_hasMaximizeButton = hasMaximizeButton;
}

bool cogui::window::hasCloseButton() const
{
    return m_hasCloseButton;
}

void cogui::window::setHasCloseButton(bool hasCloseButton)
{
    m_hasCloseButton = hasCloseButton;
}

bool cogui::window::resizeable() const
{
    return m_resizeable;
}

void cogui::window::setResizeable(bool resizeable)
{
    m_resizeable = resizeable;
}

std::wstring cogui::window::title() const
{
    return m_title;
}

void cogui::window::setTitle(const std::wstring &title)
{
    m_title = title;
}
