#include "input.h"
#include "desktop.h"
#include "mouse.h"

#include <gpm.h>
#include <ncursesw/ncurses.h>
#include <linux/keyboard.h>
#include <string.h>
#include <chrono>
#include "loguru.h"

static cogui::mouse::button last_button = cogui::mouse::button::none;
static auto t_start = std::chrono::high_resolution_clock::now();
// the work...



int my_handler(Gpm_Event *event, void *data)
{
    // info() << "Event Type: " <<  event->type << " at " <<  event->x << "," << event->y << " buttons:" << (int)event->buttons;

    cogui::mouse::get().setX(event->x - 1);
    cogui::mouse::get().setY(event->y - 1);

    if(event->type == GPM_DOWN && event->buttons == GPM_B_LEFT) //
    {
        info() << "Event Type: LEFT DOWN at " <<  event->x << "," << event->y;
        t_start = std::chrono::high_resolution_clock::now();
        last_button = cogui::mouse::button::left;
        cogui::desktop::get().handle_mouse_left_down(event->x - 1, event->y - 1);
    }

    if(event->type == GPM_DOWN && event->buttons == GPM_B_RIGHT) //
    {
        info() << "Event Type: RIGHT DOWN at " <<  event->x << "," << event->y;
        last_button = cogui::mouse::button::right;
        cogui::desktop::get().handle_mouse_right_down(event->x - 1, event->y - 1);
    }

    if(event->type & GPM_UP) //
    {

        if(last_button == cogui::mouse::button::left)
        {
            auto t_end = std::chrono::high_resolution_clock::now();

            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
            if(elapsed_time_ms < 200) // this was a fast exchange handle it as a click
            {
                info() << "Event Type: LEFT CLICK at " <<  event->x << "," << event->y;
                cogui::desktop::get().handle_mouse_left_click(event->x - 1, event->y - 1);
            }
            else
            {
                info() << "Event Type: LEFT UP at " <<  event->x << "," << event->y;
                cogui::desktop::get().handle_mouse_left_up(event->x - 1, event->y - 1);
            }
        }
        if(last_button == cogui::mouse::button::right)
        {
            info() << "Event Type: RIGHT UP at " <<  event->x << "," << event->y;
            cogui::desktop::get().handle_mouse_right_up(event->x - 1, event->y - 1);
        }
        last_button = cogui::mouse::button::none;
    }

    // as a last resort, this is a move
    cogui::desktop::get().handle_mouse_move(event->x - 1, event->y - 1);

    memset(event, 0, sizeof(Gpm_Event));

    return 0;
}

cogui::gpm_input::gpm_input()
{
}

cogui::gpm_input::~gpm_input()
{
    shutdown();
}

bool cogui::gpm_input::init()
{
    Gpm_Connect conn;

    conn.eventMask  = ~0;   /* Want to know about all the events */
    conn.defaultMask = 0;   /* don't handle anything by default  */
    conn.minMod     = 0;    /* want everything                   */
    conn.maxMod     = ~0;   /* all modifiers included            */



    if(Gpm_Open(&conn, 0) == -1)
    {
        info() << "Cannot connect to mouse server\n";
        return false;
    }

    initscr();
    clear();
    noecho();
    cbreak();
    printf("\033[?1003h\n");
    fflush(stdout);


    curs_set(0);
    gpm_handler = my_handler;
    gpm_visiblepointer = 1;

    return true;
}

bool cogui::gpm_input::shutdown()
{
    Gpm_Close();
}

std::vector<cogui::event> cogui::gpm_input::get_next_event()
{
    std::vector<cogui::event> result;
    info() << "Waiting for standard";
    int c = Gpm_Getc(stdin);
    auto e = cogui::to_event(c);
    result.push_back(e);
    return result;
}