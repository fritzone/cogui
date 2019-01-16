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

        LOG_S(INFO) << "event:" << (int)c;

            case event::press_escape:
            {
                return 0;
            }

            case event::mouse_move:
            {
                LOG_S(INFO) << "move: " << mouse::get().x() << "x" << mouse::get().y();

                desktop::get().graphics()->handle_mouse_movement();
                break;
            }

            case event::mouse_left_click:
            {
                LOG_S(INFO) << "click: " << mouse::get().x() << "x" << mouse::get().y();
                desktop::get().handle_mouse_left_click(mouse::get().x(), mouse::get().y());
                break;
            }

            case event::mouse_left_press:
            {
                LOG_S(INFO) << "press: " << mouse::get().x() << "x" << mouse::get().y();
                desktop::get().handle_mouse_left_down(mouse::get().x(), mouse::get().y());
                break;
            }

            break;
        }
    }
}
