#define _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE 600

#define MAX_DESKTOP_SIZE 4096

#include "graphics.h"
#include "events.h"
#include "mouse.h"

#include <wchar.h>

#include <ncursesw/ncurses.h>
#include <sstream>

#include "loguru.h"

cogui::graphics::graphics()
{

}

cogui::graphics::~graphics()
{
    endwin();
}

bool cogui::graphics::initialize()
{
    stdscr = initscr();

    if(stdscr == nullptr)
    {
        return false;
    }

    for(int i=0; i< MAX_DESKTOP_SIZE; i++)
    {
        std::vector<wchar_t> row;
        for(int j=0; j< MAX_DESKTOP_SIZE; j++)
        {
            row.push_back(L' ');
        }
        chars.push_back(row);
    }

    start_color();

    setlocale(LC_ALL, "");
    init_pair(1, COLOR_BLACK, COLOR_RED);   // the text mouse cursor
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // the normal text

    keypad(stdscr, TRUE);
    noecho();

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    // Makes the terminal report mouse movement events
    printf("\033[?1003h\n");

    //Hide the cursor
    printf("\033[?25l\n");
    printf("\033[?25h\n");

    fflush(stdout) ;

    curs_set(0);

    // screen size
    getmaxyx(stdscr, m_height, m_width);

    refresh();

    return true;
}

bool cogui::graphics::set_chars(int x, int y, const std::wstring &s)
{

    int l = static_cast<int>(s.length());
    for(int i=x; i<x+l; i++)
    {
        if(y > 0 && i > 0 && i < MAX_DESKTOP_SIZE && y < MAX_DESKTOP_SIZE)
        {
            chars[y][i] = s[i-x];
        }
    }
    return true;
}
void cogui::graphics::draw(int x, int y, const wchar_t *s)
{
    auto sl = wcslen(s);

    std::wstring ws(s);
    // your new String
    std::string str(ws.begin(), ws.end());
    // Show String

    if(sl + x > m_width)
    {
        for(auto sc = 0; sc + x < m_width ; sc++)
        {
            wchar_t c[2] = {0};
            c[0] = s[sc];
            mvwaddwstr(stdscr, y, sc + x, c);
        }
        return;
    }

    if(x < 0)
    {
        info() << "x=" << x << " ax=" << std::abs(x) + 1;

        std::wstring sw(s);
        std::wstring subs = sw.substr(std::abs(x) + 1);
        mvwaddwstr(stdscr, y, 0, subs.c_str());
        return;
    }

    mvwaddwstr(stdscr, y, x, s);

}

void cogui::graphics::refresh_screen()
{
    refresh();
}

cogui::event cogui::graphics::get_next_event()
{
    int c = wgetch(stdscr);
    return cogui::to_event(c);
}

void cogui::graphics::handle_mouse_movement()
{
   /* {
        static int prev_x = -1;
        static int prev_y = -1;
        static wchar_t prev_char = 0;

        int my = mouse::get().y();
        int mx = mouse::get().x();
        wchar_t char_at = chars[my][mx];

        wchar_t cc[2] = {0};
        cc[0] = char_at;

        attron(COLOR_PAIR(2));
        std::wstringstream ws;
        ws << "x:" << mx << " y:" << my << " c:" << cc << "  ";
        //mvaddwstr(22, 0, ws.str().c_str());


        if(prev_char)
        {
            wchar_t cc2[2] = {0};
            cc2[0] = prev_char;
            std::wstringstream ws2;
            ws2 << cc2;
            attron(COLOR_PAIR(2));

            mvaddwstr(prev_y, prev_x, ws2.str().c_str());

        }

        attron(COLOR_PAIR(1));
        mvaddwstr(my, mx, cc);

        prev_x = mx;
        prev_y = my;
        prev_char = char_at;

        wmove(stdscr, 0, 0);
        attron(COLOR_PAIR(2));

        refresh();
    }*/
}
