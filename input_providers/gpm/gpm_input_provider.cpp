#include "gpm_input_provider.h"
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

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;
static cogui::mouse::button last_button = cogui::mouse::button::none;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
//    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int mgetch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

static auto t_start = std::chrono::high_resolution_clock::now();
static timer dblClickTimer;
static std::mutex mouseLocker;
static bool send_click = false;

extern "C" cogui::input_provider* create()
{
    return static_cast<cogui::input_provider*>(new cogui::input_providers::gpm_input);
}

int cogui::input_providers::gpm_input::my_handler(Gpm_Event *event, void *)
{
    //    std::lock_guard<std::mutex> lk(mouseLocker);

    log_info() << "Event Type: " <<  event->type << " at " <<  event->x << "," << event->y
               << " buttons:" << (int)event->buttons << "modifiers:" << event->modifiers;

    cogui::mouse::get().setX(event->x - 1);
    cogui::mouse::get().setY(event->y - 1);

    // return value encoded as:
    // 90000 - a mouse move event
    // 900YX - to start with
    // 9001X - Down a button
    // 9002X - Up a button
    // 9003X - Click a button
    // 9004X - Double click a button
    // and X = 1 - Left, 2 - Right, 3 - Middle button

    if(event->type & GPM_DOWN && event->buttons & GPM_B_LEFT) //
    {
        t_start = std::chrono::high_resolution_clock::now();
        last_button = cogui::mouse::button::left;
        return 90011;
    }

    if(event->type & GPM_DOWN && event->buttons & GPM_B_RIGHT) //
    {
        last_button = cogui::mouse::button::right;
        return 90012;
    }

    if(event->type & GPM_UP && event->type & GPM_SINGLE) //
    {

        if(last_button == cogui::mouse::button::left)
        {
            auto t_end = std::chrono::high_resolution_clock::now();

            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

            if(elapsed_time_ms < 200) // this was a fast exchange handle it as a click
            {
                last_button = cogui::mouse::button::none;
                return 90031;
            }
            else    // simply mouse up
            {
                last_button = cogui::mouse::button::none;
                return 90021;
            }
        }
        if(last_button == cogui::mouse::button::right)
        {
            last_button = cogui::mouse::button::none;
            return 90022;
        }
    }

    if(event->type & GPM_UP && event->type & GPM_DOUBLE) //
    {
        dblClickTimer.stop();
        if(last_button == cogui::mouse::button::left)
        {
            auto t_end = std::chrono::high_resolution_clock::now();

            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

            if(elapsed_time_ms < 200) // this was a fast exchange handle it as a click
            {
                last_button = cogui::mouse::button::none;
                return 90041;
            }
            else    // simply mouse up
            {
                last_button = cogui::mouse::button::none;
                return 90021;
            }
        }
        if(last_button == cogui::mouse::button::right)
        {
            last_button = cogui::mouse::button::none;
            return 90042;
        }

    }

    // as a last resort, this is a move

    return 90000;
}

cogui::input_providers::gpm_input::~gpm_input()
{
    shutdown();
}

bool cogui::input_providers::gpm_input::init()
{

    // attempt to connect to the GPM server
    //    gpm_zerobased = 1;
    //    gpm_visiblepointer = 1;

    Gpm_Connect gc;
    gc.eventMask   = ~0;
    gc.defaultMask = 0;
    gc.minMod      = 0;
    gc.maxMod      = ~0;
    gpm_visiblepointer = 1;

    gpmFd = Gpm_Open( &gc, 0 ) < 0;
    log_debug() << "Gpm_Open="<< gpmFd;

    if( gpmFd < 0 )
    {
        log_error() << "Cannot connect to mouse server";
        return false;
    }
    gpm_visiblepointer = 1;
    gpm_handler = my_handler;

    printf("\033[?1003h\n");
    mouse::get().set_cursor_emulation(true);
    return true;
}

bool cogui::input_providers::gpm_input::shutdown()
{
    printf("\033[?1003l\n");
    printf("\033[?9l\n");

    Gpm_Close();
    return true;
}

struct s_keymap
{
    std::string keyname;
    std::vector<int> keyseq;
    cogui::events::key_class kc;
    bool alt;
    bool shift;
    bool ctrl;
};

static s_keymap keymap[]
{
     {"f1", {27, 91, 91, 65}, cogui::events::key_class::key_f1, false, false, false},
     {"f2", {27, 91, 91, 66}, cogui::events::key_class::key_f2, false, false, false},
     {"f3", {27, 91, 91, 67}, cogui::events::key_class::key_f3, false, false, false},
     {"f4", {27, 91, 91, 68}, cogui::events::key_class::key_f4, false, false, false},
     {"f5", {27, 91, 91, 69}, cogui::events::key_class::key_f5, false, false, false},
     {"f6", {27, 91, 49, 55, 126 }, cogui::events::key_class::key_f6, false, false, false},
     {"f7", {27, 91, 49, 56, 126 }, cogui::events::key_class::key_f7, false, false, false},
     {"f8", {27, 91, 49, 57, 126 }, cogui::events::key_class::key_f8, false, false, false},
     {"f9", {27, 91, 50, 48, 126 }, cogui::events::key_class::key_f9, false, false, false},
     {"f10", {27, 91, 50, 49, 126 }, cogui::events::key_class::key_f10, false, false, false},
     {"f11", {27, 91, 50, 51, 126 }, cogui::events::key_class::key_f11, false, false, false},
     {"f12", {27, 91, 50, 52, 126}, cogui::events::key_class::key_f12, false, false, false },
     {"Shift-f1", {27, 91, 50, 53, 126}, cogui::events::key_class::key_f1, false, true, false},
     {"Shift-f2", {27, 91, 50, 54, 126}, cogui::events::key_class::key_f2, false, true, false},
     {"Shift-f3", {27, 91, 50, 56, 126}, cogui::events::key_class::key_f3, false, true, false},
     {"Shift-f4", {27, 91, 50, 57, 126}, cogui::events::key_class::key_f4, false, true, false},
     {"Shift-f5", {27, 91, 51, 49, 126}, cogui::events::key_class::key_f5, false, true, false},
     {"Shift-f6", {27, 91, 51, 50, 126}, cogui::events::key_class::key_f6, false, true, false},
     {"Shift-f7", {27, 91, 51, 51, 126}, cogui::events::key_class::key_f7, false, true, false},
     {"Shift-f8", {27, 91, 51, 52, 126}, cogui::events::key_class::key_f8, false, true, false},
     //{"Shift-f9", {}, cogui::events::key_class::key_f9, false, true, false},
     //{"Shift-f10", {}, cogui::events::key_class::key_f10, false, true, false},
     //{"Shift-f11", {}, cogui::events::key_class::key_f11, false, true, false},
     //{"Shift-f12", {}, cogui::events::key_class::key_f12, false, true, false},
     {"Insert", {27, 91, 50, 126}, cogui::events::key_class::key_insert, false, false, false },
     {"Delete", {27, 91, 51, 126}, cogui::events::key_class::key_delete, false, false, false },
     {"Home", {27, 91, 49, 126}, cogui::events::key_class::key_home, false, false, false },
     {"End", {27, 91, 52, 126}, cogui::events::key_class::key_end, false, false, false },
     {"PgUp", {27, 91, 53, 126}, cogui::events::key_class::key_pgup, false, false, false },
     {"PgDn", {27, 91, 54, 126}, cogui::events::key_class::key_pgdn, false, false, false },
     {"Left", {27, 79, 68}, cogui::events::key_class::key_left, false, false, false },
     {"Up", {27, 79, 65}, cogui::events::key_class::key_up, false, false, false },
     {"Down", {27, 79, 66}, cogui::events::key_class::key_down, false, false, false },
     {"Right", {27, 79, 67}, cogui::events::key_class::key_right, false, false, false },
     {"Tab", {9}, cogui::events::key_class::key_tab, false, false, false },
     {"Space", {32}, cogui::events::key_class::key_space, false, false, false },
     {"Return", {13}, cogui::events::key_class::key_return, false, false, false },
        {"Escape", {27}, cogui::events::key_class::key_escape, false, false, false },
     {"Backspace", {127}, cogui::events::key_class::key_backspace, false, false, false },
     {"Alt-a", {27, 97}, cogui::events::key_class::key_a, true, false, false },
     {"Alt-b", {27, 98}, cogui::events::key_class::key_b, true, false, false },
     {"Alt-c", {27, 99}, cogui::events::key_class::key_c, true, false, false },
     {"Alt-d", {27, 100}, cogui::events::key_class::key_d, true, false, false },
     {"Alt-e", {27, 101}, cogui::events::key_class::key_e, true, false, false },
     {"Alt-f", {27, 102}, cogui::events::key_class::key_f, true, false, false },
     {"Alt-g", {27, 103}, cogui::events::key_class::key_g, true, false, false },
     {"Alt-h", {27, 104}, cogui::events::key_class::key_h, true, false, false },
     {"Alt-i", {27, 105}, cogui::events::key_class::key_i, true, false, false },
     {"Alt-j", {27, 106}, cogui::events::key_class::key_j, true, false, false },
     {"Alt-k", {27, 107}, cogui::events::key_class::key_k, true, false, false },
     {"Alt-l", {27, 108}, cogui::events::key_class::key_l, true, false, false },
     {"Alt-m", {27, 109}, cogui::events::key_class::key_m, true, false, false },
     {"Alt-n", {27, 110}, cogui::events::key_class::key_n, true, false, false },
     {"Alt-o", {27, 111}, cogui::events::key_class::key_o, true, false, false },
     {"Alt-p", {27, 112}, cogui::events::key_class::key_p, true, false, false },
     {"Alt-q", {27, 113}, cogui::events::key_class::key_q, true, false, false },
     {"Alt-r", {27, 114}, cogui::events::key_class::key_r, true, false, false },
     {"Alt-s", {27, 115}, cogui::events::key_class::key_s, true, false, false },
     {"Alt-t", {27, 116}, cogui::events::key_class::key_t, true, false, false },
     {"Alt-u", {27, 117}, cogui::events::key_class::key_u, true, false, false },
     {"Alt-v", {27, 118}, cogui::events::key_class::key_v, true, false, false },
     {"Alt-w", {27, 119}, cogui::events::key_class::key_w, true, false, false },
     {"Alt-x", {27, 120}, cogui::events::key_class::key_x, true, false, false },
     {"Alt-y", {27, 121}, cogui::events::key_class::key_y, true, false, false },
     {"Alt-z", {27, 122}, cogui::events::key_class::key_z, true, false, false },
        {"Alt-Shift-a", {27, 65}, cogui::events::key_class::key_a, true, true, false },
        {"Alt-Shift-b", {27, 66}, cogui::events::key_class::key_b, true, true, false },
        {"Alt-Shift-c", {27, 67}, cogui::events::key_class::key_c, true, true, false },
        {"Alt-Shift-d", {27, 68}, cogui::events::key_class::key_d, true, true, false },
        {"Alt-Shift-e", {27, 69}, cogui::events::key_class::key_e, true, true, false },
        {"Alt-Shift-f", {27, 70}, cogui::events::key_class::key_f, true, true, false },
        {"Alt-Shift-g", {27, 71}, cogui::events::key_class::key_g, true, true, false },
        {"Alt-Shift-h", {27, 72}, cogui::events::key_class::key_h, true, true, false },
        {"Alt-Shift-i", {27, 73}, cogui::events::key_class::key_i, true, true, false },
        {"Alt-Shift-j", {27, 74}, cogui::events::key_class::key_j, true, true, false },
        {"Alt-Shift-k", {27, 75}, cogui::events::key_class::key_k, true, true, false },
        {"Alt-Shift-l", {27, 76}, cogui::events::key_class::key_l, true, true, false },
        {"Alt-Shift-m", {27, 77}, cogui::events::key_class::key_m, true, true, false },
        {"Alt-Shift-n", {27, 78}, cogui::events::key_class::key_n, true, true, false },
        {"Alt-Shift-o", {27, 79}, cogui::events::key_class::key_o, true, true, false },
        {"Alt-Shift-p", {27, 80}, cogui::events::key_class::key_p, true, true, false },
        {"Alt-Shift-q", {27, 81}, cogui::events::key_class::key_q, true, true, false },
        {"Alt-Shift-r", {27, 82}, cogui::events::key_class::key_r, true, true, false },
        {"Alt-Shift-s", {27, 83}, cogui::events::key_class::key_s, true, true, false },
        {"Alt-Shift-t", {27, 84}, cogui::events::key_class::key_t, true, true, false },
        {"Alt-Shift-u", {27, 85}, cogui::events::key_class::key_u, true, true, false },
        {"Alt-Shift-v", {27, 86}, cogui::events::key_class::key_v, true, true, false },
        {"Alt-Shift-w", {27, 87}, cogui::events::key_class::key_w, true, true, false },
        {"Alt-Shift-x", {27, 88}, cogui::events::key_class::key_x, true, true, false },
        {"Alt-Shift-y", {27, 89}, cogui::events::key_class::key_y, true, true, false },
        {"Alt-Shift-z", {27, 90}, cogui::events::key_class::key_z, true, true, false },
        {"Ctrl-Alt-a", {27, 1}, cogui::events::key_class::key_a, true, false, true },
        {"Ctrl-Alt-b", {27, 2}, cogui::events::key_class::key_b, true, false, true },
        {"Ctrl-Alt-c", {27, 3}, cogui::events::key_class::key_c, true, false, true },
        {"Ctrl-Alt-d", {27, 4}, cogui::events::key_class::key_d, true, false, true },
        {"Ctrl-Alt-e", {27, 5}, cogui::events::key_class::key_e, true, false, true },
        {"Ctrl-Alt-f", {27, 6}, cogui::events::key_class::key_f, true, false, true },
        {"Ctrl-Alt-g", {27, 7}, cogui::events::key_class::key_g, true, false, true },
        {"Ctrl-Alt-h", {27, 263}, cogui::events::key_class::key_h, true, false, true },
        {"Ctrl-Alt-i", {27, 9}, cogui::events::key_class::key_i, true, false, true },
        {"Ctrl-Alt-j", {27, 10}, cogui::events::key_class::key_j, true, false, true },
        {"Ctrl-Alt-k", {27, 11}, cogui::events::key_class::key_k, true, false, true },
        {"Ctrl-Alt-l", {27, 12}, cogui::events::key_class::key_l, true, false, true },
        {"Ctrl-Alt-m", {27, 13}, cogui::events::key_class::key_m, true, false, true },
        {"Ctrl-Alt-n", {27, 14}, cogui::events::key_class::key_n, true, false, true },
        {"Ctrl-Alt-o", {27, 15}, cogui::events::key_class::key_o, true, false, true },
        {"Ctrl-Alt-p", {27, 16}, cogui::events::key_class::key_p, true, false, true },
        {"Ctrl-Alt-q", {27, 17}, cogui::events::key_class::key_q, true, false, true },
        {"Ctrl-Alt-r", {27, 18}, cogui::events::key_class::key_r, true, false, true },
        {"Ctrl-Alt-s", {27, 19}, cogui::events::key_class::key_s, true, false, true },
        {"Ctrl-Alt-t", {27, 20}, cogui::events::key_class::key_t, true, false, true },
        {"Ctrl-Alt-u", {27, 21}, cogui::events::key_class::key_u, true, false, true },
        {"Ctrl-Alt-v", {27, 22}, cogui::events::key_class::key_v, true, false, true },
        {"Ctrl-Alt-w", {27, 23}, cogui::events::key_class::key_w, true, false, true },
        {"Ctrl-Alt-x", {27, 24}, cogui::events::key_class::key_x, true, false, true },
        {"Ctrl-Alt-y", {27, 25}, cogui::events::key_class::key_y, true, false, true },
        {"Ctrl-Alt-z", {27, 26}, cogui::events::key_class::key_z, true, false, true },
     {"1", {49}, cogui::events::key_class::key_1, false, false, false },
     {"2", {50}, cogui::events::key_class::key_2, false, false, false },
     {"3", {51}, cogui::events::key_class::key_3, false, false, false },
     {"4", {52}, cogui::events::key_class::key_4, false, false, false },
     {"5", {53}, cogui::events::key_class::key_5, false, false, false },
     {"6", {54}, cogui::events::key_class::key_6, false, false, false },
     {"7", {55}, cogui::events::key_class::key_7, false, false, false },
     {"8", {56}, cogui::events::key_class::key_8, false, false, false },
     {"9", {57}, cogui::events::key_class::key_9, false, false, false },
     {"0", {48}, cogui::events::key_class::key_0, false, false, false },
     {"KP0", {27, 79, 112}, cogui::events::key_class::key_kp_0, false, false, false },
     {"KP1", {27, 79, 113}, cogui::events::key_class::key_kp_1, false, false, false },
     {"KP2", {27, 79, 114}, cogui::events::key_class::key_kp_2, false, false, false },
     {"KP3", {27, 79, 115}, cogui::events::key_class::key_kp_3, false, false, false },
     {"KP4", {27, 79, 116}, cogui::events::key_class::key_kp_4, false, false, false },
     {"KP5", {27, 79, 117}, cogui::events::key_class::key_kp_5, false, false, false },
     {"KP6", {27, 79, 118}, cogui::events::key_class::key_kp_6, false, false, false },
     {"KP7", {27, 79, 119}, cogui::events::key_class::key_kp_7, false, false, false },
     {"KP8", {27, 79, 120}, cogui::events::key_class::key_kp_8, false, false, false },
     {"KP9", {27, 79, 121}, cogui::events::key_class::key_kp_9, false, false, false },
     {"KPcomma", {27, 79, 110}, cogui::events::key_class::key_kp_comma, false, false, false },
     {"KPdiv", {27, 79, 81}, cogui::events::key_class::key_kp_div, false, false, false },
     {"KPmul", {27, 79, 82}, cogui::events::key_class::key_kp_mul, false, false, false },
     {"KPminus", {27, 79, 83}, cogui::events::key_class::key_kp_minus, false, false, false },
     {"KPplus", {27, 79, 108}, cogui::events::key_class::key_kp_plus, false, false, false },
     {"KPenter", {27, 79, 77}, cogui::events::key_class::key_kp_enter, false, false, false },
};

std::vector<std::shared_ptr<cogui::events::event>> cogui::input_providers::gpm_input::get_next_event()
{
    std::vector<std::shared_ptr<cogui::events::event>> result;

    int c = Gpm_Getc( stdin );

    int col = mouse::get().x();
    int line = mouse::get().y();

    if(c >= 90000)
    {
        switch(c)
        {
        case 90011: // left down
            result.push_back(cogui::events::event::create<cogui::events::mouse_left_down>(col, line));
            break;
        case 90012: // right down
            result.push_back(cogui::events::event::create<cogui::events::mouse_right_down>(col, line));
            break;
        case 90031: // left click
            result.push_back(cogui::events::event::create<cogui::events::mouse_left_click>(col, line));
            break;
        case 90021: // left up
            result.push_back(cogui::events::event::create<cogui::events::mouse_left_up>(col, line));
            break;
        case 90022: // right up
            result.push_back(cogui::events::event::create<cogui::events::mouse_right_up>(col, line));
            break;
        case 90041: // left double
            break;
        case 90000: // mouse move
            result.push_back(cogui::events::event::create<cogui::events::mouse_move>(col, line));
            break;
        }
    }
    else
    {
        int queued = Gpm_CharsQueued();
        std::string key_name = keyname(c);
        log_debug() << "K=" << c  << " N=" << key_name << "Q=" << queued;

        // first: sort out the Ctrl characters, like: ^A, but skipping plain Escape and Enter
        if(key_name.length() >= 2 && key_name[0] == '^' && key_name[1] != '[' && key_name[1] != 'M')
        {
            char k = tolower(key_name[1]);
            char s[2] = {0,0};
            s[0] = k;
            result.push_back(cogui::events::event::create<cogui::events::keypress>(cogui::events::key_class::key_textinput,
                                                                                   false, false, true,
                                                                                   cogui::utils::std2ws(s)));
            return result;
        }

        if(c == 27)
        {
            keypad(NULL, TRUE);

            int ck = 0;
            std::vector<int> current_seq;
            current_seq.push_back(27);

            while((ck = getch()) != ERR)
            {
                current_seq.push_back(ck);
                if(ck == 27)
                {
                    break;
                }
            }

            {
            std::stringstream ss;
            for(const auto& k : current_seq)
            {
                ss << " " << k;
            }
            log_debug() << "GOT:" << ss.str();
            }

            for(const auto& kme : keymap)
            {
                if(current_seq == kme.keyseq)
                {
                    log_debug() << "Found:" << kme.keyname;
                    result.push_back(cogui::events::event::create<cogui::events::keypress>(kme.kc,
                                                                                           kme.alt, kme.shift, kme.ctrl,
                                                                                           cogui::utils::std2ws(kme.keyname)));
                    return result;
                }
            }

            log_debug() << "Leaving";
        }
        else
        {
            if(isalnum(c) || ispunct(c))
            {
                char s[2] = {0,0};
                s[0] = c;
                result.push_back(cogui::events::event::create<cogui::events::keypress>(cogui::events::key_class::key_textinput,
                                                                                       false, false, false,
                                                                                       cogui::utils::std2ws(s)));
                return result;
            }
            std::vector<int> current_seq;
            current_seq.push_back(c);
            for(const auto& kme : keymap)
            {
                if(current_seq == kme.keyseq)
                {
                    log_debug() << "Found:" << kme.keyname;
                    result.push_back(cogui::events::event::create<cogui::events::keypress>(kme.kc,
                                                                                           kme.alt, kme.shift, kme.ctrl,
                                                                                           cogui::utils::std2ws(kme.keyname)));
                    return result;                }
            }
        }

    }
    return result;
}

std::string cogui::input_providers::gpm_input::name() const
{
    return "gpm";
}
