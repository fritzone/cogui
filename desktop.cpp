#include "desktop.h"
#include "graphics.h"
#include "theme.h"
#include "input.h"

#include "window.h"

#include <algorithm>
#define LOGURU_WITH_STREAMS 1

#include "log.h"

namespace cogui
{

desktop::desktop() : m_theme(new theme), m_graphics(new graphics), m_input(new gpm_input)
{
}

bool desktop::initialize()
{
    bool b = true;
    gpm_input* gim = dynamic_cast<gpm_input*>(m_input.get());
    if(gim)
    {
        b &= gim->init();
    }

    b &= m_graphics->initialize();
    if(!gim)
    {
        b &= m_input->init();
    }

    if(b)
    {
        m_graphics->refresh_screen();
    }
    return b;
}

std::vector<window *> desktop::windows() const
{
    return m_windows;
}

void desktop::handle_mouse_move(int x, int y)
{
    if(m_captured_window)
    {
        m_captured_window->mouse_move(x, y);
    }
    else {
//        debug() << "No window is captured right now";
    }
}

void desktop::handle_mouse_left_click(int x, int y)
{
    for(const auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            w->click( x, y);
        }
    }
}

void desktop::handle_mouse_left_down(int x, int y)
{
    for(const auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            log_info() << "captured a window";

            w->left_mouse_down(x, y);
            if(w->getDrawState() != window::draw_state::normal)
            {
                log_info() << "captured a window";
                m_captured_window = w;
                return;
            }
        }
    }
}

void desktop::handle_mouse_left_up(int x, int y)
{
    if(m_captured_window)
    {
        if(m_captured_window->inside(x, y))
        {
            m_captured_window->left_mouse_up(x, y);
        }
    }
}

void desktop::handle_mouse_right_down(int x, int y)
{
    for(const auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            w->right_mouse_down(x, y);
        }
    }
}

void desktop::handle_mouse_right_up(int x, int y)
{
    if(m_captured_window)
    {
        if(m_captured_window->inside(x, y))
        {
            m_captured_window->right_mouse_up(x, y);
        }
    }
}

void desktop::handle_tab()
{
    if(m_captured_window)
    {
        m_captured_window->focus_next_element();
        m_captured_window->draw();
        refresh();
    }
}

std::shared_ptr<theme> desktop::getTheme() const
{
    return m_theme;
}

std::shared_ptr<graphics> desktop::getGraphics() const
{
    return m_graphics;
}

std::shared_ptr<input> desktop::getInput() const
{
    return m_input;
}

void desktop::add_window(window *w)
{
    m_windows.push_back(w);
    if(m_captured_window == nullptr)
    {
        m_captured_window = w;
    }
}

void desktop::remove_window(window *w)
{
    m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), w), m_windows.end());
}

void desktop::maximize_window(window *w)
{
    w->maximize();
}

void desktop::refresh()
{
    getGraphics()->refresh_screen();
}

void desktop::clear()
{
    getGraphics()->clear_screen();
}

void desktop::shutdown()
{
    m_graphics->shutdown();
    m_input->shutdown();
}

void desktop::resize()
{
    m_graphics->shutdown();
    m_graphics->initialize();
    m_graphics->refresh_screen();
}

int desktop::getWidth() const {return m_graphics->getWidth();}

int desktop::getHeight() const {return m_graphics->getHeight();}

desktop &desktop::get()
{
    static desktop d;
    static bool desk_init = d.initialize();
    d.m_initialized = desk_init;
    return d;
}

}
