#include "events.h"
#include "curses.h"
#include "mouse.h"
#include "loguru.h"

void log_event(MEVENT event)
{
    std::stringstream ss;
    ss << "E@ " << event.x << ", " << event.y ;
    if(event.bstate & BUTTON1_PRESSED)
    {
        ss << " LP ";
    }
    if(event.bstate & BUTTON2_PRESSED)
    {
        ss << " RP ";
    }
    if(event.bstate & BUTTON1_RELEASED)
    {
        ss << " LR ";
    }
    if(event.bstate & BUTTON2_RELEASED)
    {
        ss << " RR ";
    }
    if(event.bstate & BUTTON1_CLICKED)
    {
        ss << " LC ";
    }
    if(event.bstate & BUTTON2_CLICKED)
    {
        ss << " RC ";
    }

    ss << " V:" << (static_cast<int>(event.bstate));

    info() << ss.str();

}

cogui::event cogui::to_event(int c)
{
    info() << "Event:" << c;
    switch (c) {
    case KEY_MOUSE:
    {
        MEVENT event = {0};

        int prev_x = mouse::get().x();
        int prev_y = mouse::get().y();
        bool moved = false;

        if(getmouse(&event) == OK)
        {

            log_event(event);

            if(prev_x != event.x || prev_y != event.y)
            {
                mouse::get().setX(event.x);
                mouse::get().setY(event.y);
                moved = true;
            }
            if(event.bstate & BUTTON1_PRESSED)
            {
                mouse::get().set_button(mouse::button::left);
                return cogui::event::mouse_left_press;
            }
            if(event.bstate & BUTTON2_PRESSED)
            {
                mouse::get().set_button(mouse::button::right);
                return cogui::event::mouse_right_press;
            }
            if(event.bstate & BUTTON1_RELEASED)
            {
                mouse::get().clear_button(mouse::button::left);
                return cogui::event::mouse_left_release;
            }
            if(event.bstate & BUTTON2_RELEASED)
            {
                mouse::get().clear_button(mouse::button::right);
                return cogui::event::mouse_right_release;
            }
            if(event.bstate & BUTTON1_CLICKED)
            {
                return cogui::event::mouse_left_click;
            }
            if(event.bstate & BUTTON2_CLICKED)
            {
                return cogui::event::mouse_right_click;
            }
            if(moved)
            {
                return cogui::event::mouse_move;
            }
        }
        else {
            info() << "Could not get mouse event";
        }
        break;
    }

    case 27: return cogui::event::press_escape;
    case 9: return cogui::event::press_tab;
    default: return cogui::event::unknown;
    }
    return cogui::event::unknown;
}
