#ifndef EVENTS_H
#define EVENTS_H

namespace cogui
{

enum class event
{
    press_escape,
    press_tab,
    mouse_move,
    mouse_left_click,
    mouse_right_click,
    mouse_left_press,
    mouse_left_release,
    mouse_right_press,
    mouse_right_release,
    no_event,
    unknown
};

event to_event(int);

}


#endif // EVENTS_H
