#include "application.h"
#include "desktop.h"
#include "graphics.h"

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
                return 0;
            }

            case event::mouse_move:
            {
                desktop::get().graphics()->handle_mouse_movement();
                break;
            }

            case event::mouse_left_click:
            {
                desktop::get().handle_mouse_left_click();
                break;
            }

            break;
        }
    }
}
