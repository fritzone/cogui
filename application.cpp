#include "application.h"
#include "desktop.h"
#include "graphics.h"
#include "mouse.h"
#include "window.h"
#include "input.h"
#include "events.h"

#include "loguru.h"

cogui::application::application()
{

}

int cogui::application::run()
{
    m_running = true;

    // firstly let's draw all the windows
    const auto& ws = desktop::get().windows();
    for(const auto&w : ws)
    {
        w->draw();
    }

    // then enter the loop
    while( running() )
    {
        auto events = desktop::get().getInput()->get_next_event();
        debug() << "Got:" << events.size() << " events";
        for(auto c : events)
        {
            handle_event(c);
        }
    }
}

bool cogui::application::running() const
{
    return m_running;
}

void cogui::application::stop()
{
    m_running = false;
}

void cogui::application::handle_event(cogui::event c)
{
    switch(c)
    {
    case cogui::event::press_escape:
    {
        debug() << "Escape";
        exit(1);
    }
    case cogui::event::press_tab:
    {
        desktop::get().handle_tab();
        break;
    }
    case cogui::event::mouse_left_click:
    {
        debug() << "left click: " << mouse::get().x() << "x" << mouse::get().y();
        desktop::get().handle_mouse_left_click(mouse::get().x(), mouse::get().y());
        break;
    }
    case cogui::event::mouse_left_press:
    {
        debug() << "left press: " << mouse::get().x() << "x" << mouse::get().y();
        desktop::get().handle_mouse_left_down(mouse::get().x(), mouse::get().y());
        break;
    }
    case cogui::event::mouse_left_release:
    {
        debug() << "left release: " << mouse::get().x() << "x" << mouse::get().y();
        desktop::get().handle_mouse_left_up(mouse::get().x(), mouse::get().y());
        break;
    }
    case cogui::event::mouse_move:
    {
        debug() << "move: " << mouse::get().x() << "x" << mouse::get().y();
        desktop::get().getGraphics()->handle_mouse_movement();
        desktop::get().handle_mouse_move(mouse::get().x(), mouse::get().y());
        break;
    }
    }
}
