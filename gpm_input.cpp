#include "input.h"
#include "desktop.h"
#include "mouse.h"
#include "timer.h"
#include "utils.h"

#include <gpm.h>
#include <ncursesw/ncurses.h>
#include <linux/keyboard.h>
#include <string.h>
#include <chrono>
#include "log.h"
#include <atomic>
#include <mutex>


static cogui::mouse::button last_button = cogui::mouse::button::none;
static auto t_start = std::chrono::high_resolution_clock::now();

static timer dblClickTimer;
static std::mutex mouseLocker;

std::string gpm_name(Gpm_Etype w)
{
    std::string r = "";
    if( w & GPM_MOVE ) r += " GPM_MOVE";
    if( w & GPM_DRAG ) r += " GPM_DRAG";
    if( w & GPM_DOWN ) r += " GPM_DOWN";
    if( w & GPM_UP ) r += " GPM_UP";
    if( w & GPM_SINGLE ) r += " GPM_SINGLE";
    if( w & GPM_DOUBLE ) r += " GPM_DOUBLE";
    if( w & GPM_TRIPLE ) r += " GPM_TRIPLE";
    if( w & GPM_MFLAG ) r += " GPM_MFLAG";
    if( w & GPM_HARD ) r += " GPM_HARD";
    if( w & GPM_ENTER ) r += " GPM_ENTER";
    if( w & GPM_LEAVE ) r += " GPM_LEAVE";

    return r;
}

static bool send_click = false;

int my_handler(Gpm_Event *event, void *)
{
    std::lock_guard<std::mutex> lk(mouseLocker);

    log_info() << "Event Type: " <<  event->type << " at " <<  event->x << "," << event->y << " buttons:" << (int)event->buttons;
    std::atomic<bool> handled = false;

    cogui::mouse::get().setX(event->x - 1);
    cogui::mouse::get().setY(event->y - 1);

    //log_debug() << "ET:" << event->type << "cl:" << event->clicks << " b:" << event->buttons << gpm_name(event->type);

    if(event->type == GPM_DOWN && event->buttons == GPM_B_LEFT) //
    {
        log_debug() << "Event Type: LEFT DOWN at " <<  event->x << "," << event->y;
        t_start = std::chrono::high_resolution_clock::now();
        last_button = cogui::mouse::button::left;
        handled = handled | cogui::desktop::get().handle_mouse_left_down(event->x - 1, event->y - 1);
    }

    if(event->type == GPM_DOWN && event->buttons == GPM_B_RIGHT) //
    {
        log_debug() << "Event Type: RIGHT DOWN at " <<  event->x << "," << event->y;
        last_button = cogui::mouse::button::right;
        handled = handled | cogui::desktop::get().handle_mouse_right_down(event->x - 1, event->y - 1);
    }

    if(event->type & GPM_UP && event->type & GPM_SINGLE) //
    {

        if(last_button == cogui::mouse::button::left)
        {
            auto t_end = std::chrono::high_resolution_clock::now();

            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

            if(elapsed_time_ms < 200) // this was a fast exchange handle it as a click
            {
                int x = event->x;
                int y = event->y;
                log_debug() << "Event Type: LEFT CLICK at " <<  x << "," << y;
                handled = handled | cogui::desktop::get().handle_mouse_left_click(x - 1, y - 1);
            }
            else
            {
                log_debug() << "Event Type: LEFT UP at " <<  event->x << "," << event->y;
                handled = handled | cogui::desktop::get().handle_mouse_left_up(event->x - 1, event->y - 1);
            }
        }
        if(last_button == cogui::mouse::button::right)
        {
            log_debug() << "Event Type: RIGHT UP at " <<  event->x << "," << event->y;
            handled = handled | cogui::desktop::get().handle_mouse_right_up(event->x - 1, event->y - 1);
        }
        last_button = cogui::mouse::button::none;
    }

    if(event->type & GPM_UP && event->type & GPM_DOUBLE) //
    {
        dblClickTimer.stop();
        log_debug() << "Event Type: DOUBLE CLICK at " <<  event->x << "," << event->y;
        handled = handled | cogui::desktop::get().handle_mouse_doubleclick(event->x - 1, event->y - 1);

    }


    // as a last resort, this is a move
    handled = handled | cogui::desktop::get().handle_mouse_move(event->x - 1, event->y - 1);

    memset(event, 0, sizeof(Gpm_Event));

    if(handled)
    {
        //cogui::desktop::get().redraw();
    }

    return 0;
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
        log_info() << "Cannot connect to mouse server\n";
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
    printf("\033[?1003l\n");
    printf("\033[?9l\n");

    Gpm_Close();
    return true;
}

std::vector<std::shared_ptr<cogui::events::event>> cogui::gpm_input::get_next_event()
{
    std::vector<std::shared_ptr<cogui::events::event>> result;
    //log_info() << "Waiting for standard";
    int c = Gpm_Getc(stdin);
    //auto e = cogui::to_event(c);
    //result.push_back(e);
    return result;
}


bool cogui::termkey_input::init()
{
    TERMKEY_CHECK_VERSION;
    tk = termkey_new(0, TERMKEY_FLAG_SPACESYMBOL|TERMKEY_FLAG_CTRLC);
    if(!tk) {
      fprintf(stderr, "Cannot allocate termkey instance\n");
      exit(1);
    }

    // mouse movement reported too
    printf("\033[?1003h\n");
    prev_curs = curs_set (0);
    if(prev_curs == ERR)
    {
        prev_curs = 1;
    }

}

std::vector<std::shared_ptr<cogui::events::event>> cogui::termkey_input::get_next_event()
{
    std::vector<std::shared_ptr<cogui::events::event>> result;

    TermKeyResult ret;
    TermKeyKey key;
    memset(&key, 0, sizeof (TermKeyKey));
    ret = termkey_waitkey(tk, &key);
    if(ret != TERMKEY_RES_KEY) return result;
    bool handled = false;

    if(key.type == TERMKEY_TYPE_MOUSE)
    {
        TermKeyMouseEvent ev;
        int button;
        int line, col;
        termkey_interpret_mouse(tk, &key, &ev, &button, &line, &col);
        log_info() << "Mouse:" << (col-1) << "x" <<  line-1;

        cogui::mouse::get().setX(col - 1);
        cogui::mouse::get().setY(line - 1);

        if(ev == 1) // Press
        {
            if(button == 1) // Left
            {
                t_start = std::chrono::high_resolution_clock::now();
                last_button = cogui::mouse::button::left;
//                handled = handled | cogui::desktop::get().handle_mouse_left_down(col - 1, line - 1);
                result.push_back(cogui::events::event::create<cogui::events::mouse_left_down>(col-1, line-1));
            }

            if(button == 3) // Right
            {
                last_button = cogui::mouse::button::right;
                //handled = handled | cogui::desktop::get().handle_mouse_right_down(col - 1, line - 1);
                result.push_back(cogui::events::event::create<cogui::events::mouse_right_down>(col-1, line-1));

            }

        }
        else
        if(ev == 3) // Release
        {
            if(last_button == cogui::mouse::button::left)
            {
                auto t_end = std::chrono::high_resolution_clock::now();

                double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

                if(elapsed_time_ms < 200) // this was a fast exchange handle it as a click
                {
                    log_debug() << "Event Type: LEFT CLICK at " <<  col - 1 << "," << line - 1;
//                    handled = handled | cogui::desktop::get().handle_mouse_left_click(col - 1, line - 1);
                    result.push_back(cogui::events::event::create<cogui::events::mouse_left_click>(col-1, line-1));

                }
                else
                {
                    log_debug() << "Event Type: LEFT UP at " <<  col - 1<< "," << line - 1;
                    //handled = handled | cogui::desktop::get().handle_mouse_left_up(col - 1, line - 1);
                    result.push_back(cogui::events::event::create<cogui::events::mouse_left_up>(col-1, line-1));

                }
            }
            else
            if(last_button == cogui::mouse::button::right)
            {
                log_debug() << "Event Type: RIGHT UP at " <<  col - 1 << "," << line - 1;
                //handled = handled | cogui::desktop::get().handle_mouse_right_up(col - 1, line - 1);
                result.push_back(cogui::events::event::create<cogui::events::mouse_right_up>(col-1, line-1));
            }
            else    // just move around, strangely the plain move is reported as release
            {
                //cogui::desktop::get().handle_mouse_move(col - 1, line - 1);
                result.push_back(cogui::events::event::create<cogui::events::mouse_move>(col-1, line-1));

            }


            last_button = cogui::mouse::button::none;
        }
        else
        if(ev == 2) //Drag
        {
            //cogui::desktop::get().handle_mouse_move(col - 1, line - 1);
            result.push_back(cogui::events::event::create<cogui::events::mouse_move>(col-1, line-1));

        }

    }
    else
    {
        TermKeyFormat format = TERMKEY_FORMAT_VIM;
        char buffer[50];
        termkey_strfkey(tk, buffer, sizeof buffer, &key, format);
        log_info() << buffer;

        bool alt_press = key.modifiers & TERMKEY_KEYMOD_ALT;
        bool ctrl_press = key.modifiers & TERMKEY_KEYMOD_CTRL;
        bool shift_press = key.modifiers & TERMKEY_KEYMOD_SHIFT;

        if(key.type == TERMKEY_TYPE_UNICODE) {
            result.push_back(cogui::events::event::create<cogui::events::key>(cogui::events::key_class::key_textinput,
                                                                              alt_press, shift_press, ctrl_press,
                                                                              cogui::utils::std2ws(key.utf8)));
        }
    }


    return result;
}

bool cogui::termkey_input::shutdown()
{
    printf("\033[?1003l\n");
    printf("\033[?9l\n");
    termkey_destroy(tk);
    curs_set(prev_curs);

    return true;
}
