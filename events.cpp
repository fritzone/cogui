#include "events.h"
#include "curses.h"
#include "mouse.h"
#include "log.h"
#include "cogui.h"

/*
cogui::event cogui::to_event(int c)
{
    log_info() << "Event:" << c;
    switch (c)
    {
        case KEY_MOUSE:
        {
            MEVENT event = {0,0,0,0,0};

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
            else
            {
                log_info() << "Could not get mouse event";
            }
            break;
        }

        case 27: return cogui::event::press_escape;
        case 9: return cogui::event::press_tab;
        default: return cogui::event::unknown;
    }

    return cogui::event::unknown;
}
*/

cogui::events::key::key(cogui::events::key_class type, bool alt, bool shift, bool ctrl, const std::wstring &chardata) : m_type(type),
    m_alt(alt), m_shift(shift), m_ctrl(ctrl), m_chardata(chardata)
{

}

bool cogui::events::key::handle()
{
    std::shared_ptr<cogui::events::key> copy = std::make_shared<cogui::events::key>(m_type, m_alt, m_shift, m_ctrl, m_chardata);
    return cogui::desktop::get().handle_key(copy);

}

std::wstring cogui::events::key::get_chardata()
{
    return m_chardata;
}

cogui::events::mouse_move::mouse_move(int x, int y) : mouse_event(x, y) {}

bool cogui::events::mouse_move::handle()
{
    return cogui::desktop::get().handle_mouse_move(x(),y());
}

cogui::events::mouse_event::mouse_event(int x, int y) : m_x(x), m_y(y)
{

}

int cogui::events::mouse_event::x() const
{
    return m_x;
}

int cogui::events::mouse_event::y() const
{
    return m_y;
}

cogui::events::mouse_right_up::mouse_right_up(int x, int y) : mouse_event(x, y)
{

}

bool cogui::events::mouse_right_up::handle()
{
    return cogui::desktop::get().handle_mouse_right_up(x(), y());
}

cogui::events::mouse_left_up::mouse_left_up(int x, int y) : mouse_event(x, y)
{

}

bool cogui::events::mouse_left_up::handle()
{
    return cogui::desktop::get().handle_mouse_left_up(x(), y());

}

cogui::events::mouse_left_click::mouse_left_click(int x, int y) : mouse_event(x, y)
{

}

bool cogui::events::mouse_left_click::handle()
{
    return cogui::desktop::get().handle_mouse_left_click(x(), y());
}

cogui::events::mouse_left_down::mouse_left_down(int x, int y) : mouse_event(x, y)
{

}

bool cogui::events::mouse_left_down::handle()
{
    return cogui::desktop::get().handle_mouse_left_down(x(), y());
}

cogui::events::mouse_right_down::mouse_right_down(int x, int y) : mouse_event(x, y)
{

}

bool cogui::events::mouse_right_down::handle()
{
    return cogui::desktop::get().handle_mouse_right_down(x(), y());
}
