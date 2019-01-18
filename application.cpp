#include "application.h"
#include "desktop.h"
#include "graphics.h"
#include "mouse.h"

#include "loguru.h"

cogui::application::application()
{

}

int cogui::application::run()
{

    while(1)
    {
        auto c = desktop::get().graphics()->get_next_event();
        switch(c)
        {
        case event::press_escape:
        {
            LOG_S(INFO) << "Escape";
            return 0;
        }
        case event::mouse_left_click:
        {
            LOG_S(INFO) << "left click: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_click(mouse::get().x(), mouse::get().y());
            break;
        }
        case event::mouse_left_press:
        {
            LOG_S(INFO) << "left press: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_down(mouse::get().x(), mouse::get().y());
            break;
        }
        case event::mouse_left_release:
        {
            LOG_S(INFO) << "left release: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_up(mouse::get().x(), mouse::get().y());
            break;
        }
        case event::mouse_move:
        {
            LOG_S(INFO) << "move: " << mouse::get().x() << "x" << mouse::get().y();

            desktop::get().graphics()->handle_mouse_movement();
            desktop::get().handle_mouse_move(mouse::get().x(), mouse::get().y());
            break;
        }
        }
    }
}
