#include "input.h"
#include <ncursesw/ncurses.h>

#include "log.h"

bool cogui::xterm_input::init()
{
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    mousemask(BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED
              | BUTTON2_PRESSED | BUTTON2_RELEASED | BUTTON2_CLICKED | BUTTON2_DOUBLE_CLICKED
              | BUTTON_SHIFT | BUTTON_CTRL | BUTTON_ALT
              | REPORT_MOUSE_POSITION
              ,nullptr);

    mouseinterval(500);

    // Makes the terminal report mouse movement events
    printf("\033[?1003h\n");

    //Hide the cursor
    printf("\033[?25l\n");
    printf("\033[?25h\n");

    curs_set(0);

    return true;
}

bool cogui::xterm_input::shutdown()
{

}

std::vector<std::shared_ptr<cogui::events::event>> cogui::xterm_input::get_next_event()
{
    std::vector<std::shared_ptr<cogui::events::event>> result;
    int c = ERR;
    while ((c = getch()) != ERR)
    {
        /*auto e = cogui::to_event(c);
        result.push_back(e);*/
    }
    log_debug() << "Got " << result.size() << " events ";
    return result;
}
