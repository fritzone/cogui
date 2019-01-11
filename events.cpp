#include "events.h"
#include "curses.h"
#include "mouse.h"

cogui::event cogui::to_event(int c)
{
    switch (c) {
    case KEY_MOUSE:
    {
        MEVENT event;
        if(getmouse(&event) == OK)
        {
            mouse::get().setX(event.x);
            mouse::get().setY(event.y);
            if(event.bstate & BUTTON1_CLICKED)
            {
                return cogui::event::mouse_left_click;
            }
            if(event.bstate & BUTTON2_CLICKED)
            {
                return cogui::event::mouse_right_click;
            }
        }
        return cogui::event::mouse_move;
    }

    case 27: return cogui::event::press_escape;
    default: return cogui::event::unknown;
    }
}
