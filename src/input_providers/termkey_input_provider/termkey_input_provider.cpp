#include "termkey_input_provider.h"
#include <ncursesw/ncurses.h>
#include <string.h>
#include <log.h>
#include <mouse.h>

static auto t_start = std::chrono::high_resolution_clock::now();
static cogui::mouse::button last_button = cogui::mouse::button::none;

std::map<TermKeySym, cogui::events::key_class> cogui::input_providers::termkey_input_provider::m_keymap =
    {
        {TERMKEY_SYM_UP, cogui::events::key_class::key_up},
        {TERMKEY_SYM_DOWN, cogui::events::key_class::key_down},
        {TERMKEY_SYM_LEFT, cogui::events::key_class::key_left},
        {TERMKEY_SYM_RIGHT, cogui::events::key_class::key_right},
        {TERMKEY_SYM_ESCAPE, cogui::events::key_class::key_escape},
        {TERMKEY_SYM_ENTER, cogui::events::key_class::key_return},
        {TERMKEY_SYM_TAB, cogui::events::key_class::key_tab},
        {TERMKEY_SYM_INSERT, cogui::events::key_class::key_insert},
        {TERMKEY_SYM_DELETE, cogui::events::key_class::key_delete},
        {TERMKEY_SYM_HOME, cogui::events::key_class::key_home},
        {TERMKEY_SYM_END, cogui::events::key_class::key_end},
        {TERMKEY_SYM_PAGEUP, cogui::events::key_class::key_pgup},
        {TERMKEY_SYM_PAGEDOWN, cogui::events::key_class::key_pgdn},
        {TERMKEY_SYM_BACKSPACE, cogui::events::key_class::key_backspace},
        {TERMKEY_SYM_KPDIV, cogui::events::key_class::key_kp_div},
        {TERMKEY_SYM_KPMULT, cogui::events::key_class::key_kp_mul},
        {TERMKEY_SYM_KPMINUS, cogui::events::key_class::key_kp_minus},
        {TERMKEY_SYM_KPPLUS, cogui::events::key_class::key_kp_plus},
        {TERMKEY_SYM_KPENTER, cogui::events::key_class::key_kp_enter},
        {TERMKEY_SYM_KP0, cogui::events::key_class::key_kp_0},
        {TERMKEY_SYM_KP1, cogui::events::key_class::key_kp_1},
        {TERMKEY_SYM_KP2, cogui::events::key_class::key_kp_2},
        {TERMKEY_SYM_KP3, cogui::events::key_class::key_kp_3},
        {TERMKEY_SYM_KP4, cogui::events::key_class::key_kp_4},
        {TERMKEY_SYM_KP5, cogui::events::key_class::key_kp_5},
        {TERMKEY_SYM_KP6, cogui::events::key_class::key_kp_6},
        {TERMKEY_SYM_KP7, cogui::events::key_class::key_kp_7},
        {TERMKEY_SYM_KP8, cogui::events::key_class::key_kp_8},
        {TERMKEY_SYM_KP9, cogui::events::key_class::key_kp_9}

};

cogui::input_providers::termkey_input_provider::~termkey_input_provider()
{
    log_info() << "Termkey shutting down";
}

bool cogui::input_providers::termkey_input_provider::init()
{
    TERMKEY_CHECK_VERSION;
    tk = termkey_new(0, TERMKEY_FLAG_SPACESYMBOL|TERMKEY_FLAG_CTRLC);
    if(!tk) {
        log_emergency() << "Cannot allocate termkey instance";
        exit(1);
    }

    // mouse movement reported too
    printf("\033[?1003h\n");
    prev_curs = curs_set (0);
    if(prev_curs == ERR)
    {
        prev_curs = 1;
    }
    return true;
}

std::vector<std::shared_ptr<cogui::events::event>> cogui::input_providers::termkey_input_provider::get_next_event()
{
    std::vector<std::shared_ptr<cogui::events::event>> result;

    TermKeyResult ret;
    TermKeyKey key;
    memset(&key, 0, sizeof (TermKeyKey));
    ret = termkey_waitkey(tk, &key);
    if(ret != TERMKEY_RES_KEY)
    {
        log_info() << "Nothing here, move along";
        return result;
    }
    bool handled = false;
    log_info() <<  "termkey event type:" << key.type;

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
                result.push_back(cogui::events::event::create<cogui::events::mouse_left_down>(col-1, line-1));
            }

            if(button == 3) // Right
            {
                last_button = cogui::mouse::button::right;
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
                    result.push_back(cogui::events::event::create<cogui::events::mouse_left_click>(col-1, line-1));
                }
                else
                {
                    log_debug() << "Event Type: LEFT UP at " <<  col - 1<< "," << line - 1;
                    result.push_back(cogui::events::event::create<cogui::events::mouse_left_up>(col-1, line-1));
                }
            }
            else
                if(last_button == cogui::mouse::button::right)
                {
                    log_debug() << "Event Type: RIGHT UP at " <<  col - 1 << "," << line - 1;
                    result.push_back(cogui::events::event::create<cogui::events::mouse_right_up>(col-1, line-1));
                }
                else    // just move around, strangely the plain move is reported as release
                {
                    result.push_back(cogui::events::event::create<cogui::events::mouse_move>(col-1, line-1));
                }


            last_button = cogui::mouse::button::none;
        }
        else
        if(ev == 2) //Drag
        {
            result.push_back(cogui::events::event::create<cogui::events::mouse_move>(col-1, line-1));
        }
    }
    else
    {
        TermKeyFormat format = TERMKEY_FORMAT_LONGMOD;
        char buffer[50];
        termkey_strfkey(tk, buffer, sizeof buffer, &key, format);
        log_info() << buffer << "type:" << key.type;

        bool alt_press = key.modifiers & TERMKEY_KEYMOD_ALT;
        bool ctrl_press = key.modifiers & TERMKEY_KEYMOD_CTRL;
        bool shift_press = key.modifiers & TERMKEY_KEYMOD_SHIFT;

        if(key.type == TERMKEY_TYPE_UNICODE)
        {
            result.push_back(cogui::events::event::create<cogui::events::keypress>(cogui::events::key_class::key_textinput,
                                                                                   alt_press, shift_press, ctrl_press,
                                                                                   cogui::utils::std2ws(key.utf8)));
        }
        else
        if(key.type == TERMKEY_TYPE_KEYSYM)
        {
            if(m_keymap.find(key.code.sym) != m_keymap.end())
            {
                log_info() << "Got a symbol key" << buffer;
                result.push_back(cogui::events::event::create<cogui::events::keypress>(m_keymap[key.code.sym],
                                                                                       alt_press, shift_press, ctrl_press,
                                                                                       cogui::utils::std2ws(buffer)));
            }
        }
        else
        if(key.type == TERMKEY_TYPE_FUNCTION)
        {

            //codepoint = F<<codepoint>>
            log_info() << "Got a function key" << buffer;

            static const std::map<std::string,cogui::events::key_class> function_keys{
                {"F1", cogui::events::key_class::key_f1},
                {"F2", cogui::events::key_class::key_f2},
                {"F3", cogui::events::key_class::key_f3},
                {"F4", cogui::events::key_class::key_f4},
                {"F5", cogui::events::key_class::key_f5},
                {"F6", cogui::events::key_class::key_f6},
                {"F7", cogui::events::key_class::key_f7},
                {"F8", cogui::events::key_class::key_f8},
                {"F9", cogui::events::key_class::key_f9},
                {"F10", cogui::events::key_class::key_f10},
                {"F11", cogui::events::key_class::key_f11},
                {"F12", cogui::events::key_class::key_f12}
            };


            log_debug() << (alt_press ? "AltPress" : "")  << (ctrl_press ? "CtrlPress" : "") <<  (shift_press ? "ShiftPress" : "");

            if(function_keys.find(buffer) != function_keys.end())
            {
                result.push_back(cogui::events::event::create<cogui::events::keypress>(function_keys.at(buffer),
                                                                                       alt_press, shift_press, ctrl_press,
                                                                                       cogui::utils::std2ws(buffer)));
            }
            else // function key + modifier
            {
                std::string F = "F" + std::to_string(key.code.codepoint);
                if(function_keys.find(F) != function_keys.end())
                {
                    if(strchr(buffer, '-') && *(strchr(buffer, '-') + 1) == 'F')
                    {
                        *(strchr(buffer, '-') + 1) = 'f';
                    }
                    result.push_back(cogui::events::event::create<cogui::events::keypress>(function_keys.at(F),
                                                                                           alt_press, shift_press, ctrl_press,
                                                                                           cogui::utils::std2ws(buffer)));
                }

            }
        }
    }

    return result;
}

bool cogui::input_providers::termkey_input_provider::shutdown()
{
    printf("\033[?1003l\n");
    printf("\033[?9l\n");
    termkey_destroy(tk);
    curs_set(prev_curs);

    return true;
}

std::string cogui::input_providers::termkey_input_provider::name() const
{
    return "termkey";
}
