#ifndef EVENTS_H
#define EVENTS_H

namespace cogui
{

enum class event
{
    press_escape,
    mouse_move,
    mouse_left_click,
    mouse_right_click,
    unknown
};

event to_event(int);

}


#endif // EVENTS_H
