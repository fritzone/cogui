#include "desktop.h"
#include "application.h"
#include "extension_manager.h"

#include "input_provider.h"

#include "window.h"

#include <algorithm>
#include <factory.h>
#include "log.h"

#include <mutex>

namespace cogui
{

desktop::desktop() : m_theme( factory<theme>::instance().create(g_s_theme_name) ),
                     m_rendering_engine( factory<rendering_engine>::instance().create(g_s_rendering_engine_name)),
                     m_input( factory<input_provider>::instance().create(g_s_input_provider_name) )
{
    m_rendering_engine->set_theme(m_theme);

    log_info() << "Picking theme:" << m_theme->name();
    log_info() << "Picking graphics engine:" << m_rendering_engine->name();
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

    b &= m_rendering_engine->initialize();

    if(b)
    {
        m_rendering_engine->refresh_screen();
        m_rendering_engine->set_rendering_function(renderer);
    }
    return b;
}



bool desktop::renderer()
{
    std::lock_guard<std::mutex> lock(renderMutex); // Lock the mutex for the duration of this scope

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
    if(m_captured_window && m_captured_window->has_sysmenu_button() && m_captured_window->get_system_menu().is_opened())
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
    if(k->get_chardata() == Ctrl_Alt_q::ptrCtrl_Alt_q().generator().get_chardata())
    {
        cogui::application::instance().stop();
        return true;
    }

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


theme* desktop::get_theme() const
{
    return m_theme;
}

rendering_engine* desktop::get_graphics() const
{
    return m_rendering_engine;
}

void desktop::set_theme(const std::string &name)
{
    m_theme = factory<theme>::instance().create(name);
}

input_provider* desktop::get_input() const
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
    if(m_rendering_engine) m_rendering_engine->shutdown();
    m_rendering_engine = nullptr;

    if(m_input) m_input->shutdown();
    m_input = nullptr;
}

void desktop::resize()
{
    m_rendering_engine->shutdown();
    m_rendering_engine->initialize();
    m_rendering_engine->refresh_screen();
}

int desktop::get_width() const {return m_rendering_engine->get_screen_width();}

int desktop::get_height() const {return m_rendering_engine->get_screen_height();}

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
    if(m_captured_window)
    {
        graphics()->set_clip_area(m_captured_window->get_rect());
        m_captured_window->draw();
        graphics()->set_clip_area(rect());
    }


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
