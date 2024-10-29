#include "desktop.h"

#include "extension_manager.h"

#include "input_provider.h"

#include "window.h"

#include <algorithm>
#include "log.h"




namespace cogui
{

desktop::desktop() : m_theme( g_s_theme_name.empty() ? theme_manager::instance().current_loadable() : theme_manager::instance().get_loadable(g_s_theme_name)),
                     m_graphics(g_s_rendering_engine_name.empty() ? rendering_engine_manager::instance().current_loadable() : rendering_engine_manager::instance().get_loadable(g_s_rendering_engine_name)),
                     m_input( g_s_input_provider_name .empty() ? input_provider_manager::instance().current_loadable() :input_provider_manager::instance().get_loadable(g_s_input_provider_name)  )
{
    log_info() << "Picking theme:" << m_theme->name();
    log_info() << "Picking graphics engine:" << m_graphics->name();
	log_info() << "Picking input provider engine:" << m_input->name();
}

desktop::~desktop()
{
    shutdown();
}

bool desktop::initialize()
{
    bool b = true;

    // do not change the order, input provider needs to be initialized first
    b &= m_input->init();

    b &= m_graphics->initialize();

    if(b)
    {
        m_graphics->refresh_screen();
        m_graphics->set_rendering_function(renderer);
    }
    return b;
}

bool desktop::renderer()
{
    get().redraw();
    return true;
}

const std::vector<window *> &desktop::get_windows() const
{
    return m_windows;
}

bool desktop::handle_mouse_move(int x, int y)
{
    bool handled = false;
    if(m_captured_window)
    {
        handled = m_captured_window->mouse_move(x, y);
    }
    return handled;
}

bool desktop::handle_mouse_left_click(int x, int y)
{
    bool handled = false;

    for(auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            w->click( x, y);
            handled = true;
            m_captured_window->deactivate();
            m_captured_window = w;
            m_captured_window->activate();
            break;
        }
    }

    if(handled)
    {
        return true;
    }
    if(m_captured_window && m_captured_window->has_sysmenu_button() && m_captured_window->get_system_menu().isOpened())
    {
        m_captured_window->close_current_menu();
        handled = true;
        redraw();
    }
    else
    {
        for(auto& w : m_windows)
        {
            if(w->has_sysmenu_button())
            {
                w->get_system_menu().close();
                handled = true;
            }
        }
    }

    return handled;
}

bool desktop::handle_mouse_left_down(int x, int y)
{
    bool handled = false;
    for(const auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            log_info() << "captured a window";
//			auto m_before = w->get_current_menu();
            w->left_mouse_down(x, y);
//			auto m_after = w->get_current_menu();
			log_info() << "captured a window:" << static_cast<int>( w->get_draw_state() );
			m_captured_window->deactivate();

			// see if we need to close a menu: m_before == m_after

			m_captured_window = w;
			m_captured_window->activate();
			return true;
        }
    }
    return handled;
}

bool desktop::handle_mouse_left_up(int x, int y)
{
    bool handled = false;

    if(m_captured_window)
    {
        if(m_captured_window->inside(x, y))
        {
            m_captured_window->left_mouse_up(x, y);
        }
        handled = true;
    }
    return handled;
}

bool desktop::handle_mouse_right_down(int x, int y)
{
    bool handled = false;

    for(const auto& w : m_windows)
    {
        if(w->inside(x, y))
        {
            w->right_mouse_down(x, y);
        }
        handled = true;
    }
    return handled;
}

bool desktop::handle_mouse_right_up(int x, int y)
{
    bool handled = false;

    if(m_captured_window)
    {
        if(m_captured_window->inside(x, y))
        {
            m_captured_window->right_mouse_up(x, y);
            handled = true;
        }
    }
    return handled;
}

bool desktop::handle_mouse_doubleclick(int x, int y)
{
    bool handled = false;

    if(m_captured_window)
    {
        if(m_captured_window->inside(x, y))
        {
            m_captured_window->doubleclick(x, y);
            handled = true;
        }
    }
    return handled;
}

void desktop::handle_tab()
{
    if(m_captured_window)
    {
        m_captured_window->focus_next_element();
        redraw();
    }
}

bool desktop::handle_key(std::shared_ptr<cogui::events::keypress> k)
{
    if(m_captured_window)
    {
		if(k->get_chardata() == L"Tab")
		{
			m_captured_window->focus_next_element();
			return true;
		}
        return m_captured_window->keypress(k);
    }
    return false;
}


std::shared_ptr<theme> desktop::get_theme() const
{
    return m_theme;
}

std::shared_ptr<rendering_engine> desktop::get_graphics() const
{
    return m_graphics;
}

std::shared_ptr<input_provider> desktop::get_input() const
{
    return m_input;
}

void desktop::add_window(window *w)
{
    m_windows.push_back(w);
    if(m_captured_window != nullptr)
    {
        m_captured_window->deactivate();
    }

    m_captured_window = w;
    m_captured_window->activate();
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
	get_graphics()->refresh_screen();
}

void desktop::clear()
{
	get_graphics()->clear_screen();
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

int desktop::get_width() const {return m_graphics->get_screen_width();}

int desktop::get_height() const {return m_graphics->get_screen_height();}

void desktop::redraw()
{
    clear();
    for(const auto& w : m_windows)
    {
        if(&w != &m_captured_window)
        {
			graphics()->set_clip_area(w->get_rect());
            w->draw();
			graphics()->set_clip_area(rect());
        }
    }
	graphics()->set_clip_area(m_captured_window->get_rect());
	m_captured_window->draw();
	graphics()->set_clip_area(rect());

}

void desktop::init(const std::string &theme_name)
{
    g_s_theme_name = theme_name;
}

desktop &desktop::get()
{
    static desktop d;
    static int init_count = 0;
    if(!d.m_initialized)
    {
        static bool desk_init = d.initialize();
        d.m_initialized = desk_init;
        if(!d.m_initialized)
        {
            log_error() << "Cannot initialize the desktop";
            init_count ++;
            if(init_count == 16)
            {
                log_emergency() << "Giving up";
                std::abort();
            }
        }
    }
    return d;
}

}
