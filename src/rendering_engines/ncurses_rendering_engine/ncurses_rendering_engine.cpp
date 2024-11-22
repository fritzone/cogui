#define _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE 600

#define MAX_DESKTOP_SIZE 4096

#include "ncurses_rendering_engine.h"
#include "events.h"
#include "mouse.h"
#include "cogui.h"
#include "desktop.h"
#include "frame.h"

#include <wchar.h>
#include <ncursesw/ncurses.h>
#include <sstream>
#include <thread>
#include <pthread.h>

#include "log.h"

namespace {
// code, index, foreground, background
static const std::map<int, std::tuple<int, int, int>> colorpairs =
{
    {-1, {-1, COLOR_BLACK, COLOR_BLACK}},
    {0, {0, COLOR_BLACK, COLOR_BLACK}},
    {1, {1, COLOR_BLACK, COLOR_RED}},
    {2, {2, COLOR_BLACK, COLOR_GREEN}},
    {3, {3, COLOR_BLACK, COLOR_YELLOW}},
    {4, {4, COLOR_BLACK, COLOR_BLUE}},
    {5, {5, COLOR_BLACK, COLOR_MAGENTA}},
    {6, {6, COLOR_BLACK, COLOR_CYAN}},
    {7, {7, COLOR_BLACK, COLOR_WHITE}},
    {256, {8, COLOR_RED, COLOR_BLACK}},
    {257, {9, COLOR_RED, COLOR_RED}},
    {258, {10, COLOR_RED, COLOR_GREEN}},
    {259, {11, COLOR_RED, COLOR_YELLOW}},
    {260, {12, COLOR_RED, COLOR_BLUE}},
    {261, {13, COLOR_RED, COLOR_MAGENTA}},
    {262, {14, COLOR_RED, COLOR_CYAN}},
    {263, {15, COLOR_RED, COLOR_WHITE}},
    {512, {16, COLOR_GREEN, COLOR_BLACK}},
    {513, {17, COLOR_GREEN, COLOR_RED}},
    {514, {18, COLOR_GREEN, COLOR_GREEN}},
    {515, {19, COLOR_GREEN, COLOR_YELLOW}},
    {516, {20, COLOR_GREEN, COLOR_BLUE}},
    {517, {21, COLOR_GREEN, COLOR_MAGENTA}},
    {518, {22, COLOR_GREEN, COLOR_CYAN}},
    {519, {23, COLOR_GREEN, COLOR_WHITE}},
    {768, {24, COLOR_YELLOW, COLOR_BLACK}},
    {769, {25, COLOR_YELLOW, COLOR_RED}},
    {770, {26, COLOR_YELLOW, COLOR_GREEN}},
    {771, {27, COLOR_YELLOW, COLOR_YELLOW}},
    {772, {28, COLOR_YELLOW, COLOR_BLUE}},
    {773, {29, COLOR_YELLOW, COLOR_MAGENTA}},
    {774, {30, COLOR_YELLOW, COLOR_CYAN}},
    {775, {31, COLOR_YELLOW, COLOR_WHITE}},
    {1024, {32, COLOR_BLUE, COLOR_BLACK}},
    {1025, {33, COLOR_BLUE, COLOR_RED}},
    {1026, {34, COLOR_BLUE, COLOR_GREEN}},
    {1027, {35, COLOR_BLUE, COLOR_YELLOW}},
    {1028, {36, COLOR_BLUE, COLOR_BLUE}},
    {1029, {37, COLOR_BLUE, COLOR_MAGENTA}},
    {1030, {38, COLOR_BLUE, COLOR_CYAN}},
    {1031, {39, COLOR_BLUE, COLOR_WHITE}},
    {1280, {40, COLOR_MAGENTA, COLOR_BLACK}},
    {1281, {41, COLOR_MAGENTA, COLOR_RED}},
    {1282, {42, COLOR_MAGENTA, COLOR_GREEN}},
    {1283, {43, COLOR_MAGENTA, COLOR_YELLOW}},
    {1284, {44, COLOR_MAGENTA, COLOR_BLUE}},
    {1285, {45, COLOR_MAGENTA, COLOR_MAGENTA}},
    {1286, {46, COLOR_MAGENTA, COLOR_CYAN}},
    {1287, {47, COLOR_MAGENTA, COLOR_WHITE}},
    {1536, {48, COLOR_CYAN, COLOR_BLACK}},
    {1537, {49, COLOR_CYAN, COLOR_RED}},
    {1538, {50, COLOR_CYAN, COLOR_GREEN}},
    {1539, {51, COLOR_CYAN, COLOR_YELLOW}},
    {1540, {52, COLOR_CYAN, COLOR_BLUE}},
    {1541, {53, COLOR_CYAN, COLOR_MAGENTA}},
    {1542, {54, COLOR_CYAN, COLOR_CYAN}},
    {1543, {55, COLOR_CYAN, COLOR_WHITE}},
    {1792, {56, COLOR_WHITE, COLOR_BLACK}},
    {1793, {57, COLOR_WHITE, COLOR_RED}},
    {1794, {58, COLOR_WHITE, COLOR_GREEN}},
    {1795, {59, COLOR_WHITE, COLOR_YELLOW}},
    {1796, {60, COLOR_WHITE, COLOR_BLUE}},
    {1797, {61, COLOR_WHITE, COLOR_MAGENTA}},
    {1798, {62, COLOR_WHITE, COLOR_CYAN}},
    {1799, {63, COLOR_WHITE, COLOR_WHITE}},
};

}

cogui::rendering_engines::ncurses_rendering_engine::~ncurses_rendering_engine()
{
    log_info() << "Shutting down ncurses rendering engine";
    delete buffers[0];
    delete buffers[1];
}

bool cogui::rendering_engines::ncurses_rendering_engine::initialize()
{
    setenv("TERM", "xterm", 1);
    std::setlocale(LC_ALL, "");
    stdscr = initscr();

    raw();

    if(stdscr == nullptr)
    {
        return false;
    }

    if(has_colors())
    {
        start_color();
        use_default_colors();
        m_colours = true;
    }

    // initialize the colorpairs
    for(const auto& cp : colorpairs)
    {
        log_info() << "Init:" << std::get<0>(cp.second) << std::get<1>(cp.second) << std::get<2>(cp.second);

        init_pair(std::get<0>(cp.second), std::get<1>(cp.second), std::get<2>(cp.second));
    }

    fflush(stdout) ;
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    // screen size
    getmaxyx(stdscr, m_height, m_width);

    buffers[0] = new frame(m_width, m_height);
    buffers[1] = new frame(m_width, m_height);
    swap_buffers();

    return true;
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_text(int x, int y, const wchar_t *s, int flags)
{
    if(flags & textflags::v_title)
    {
        draw_title(x, y, s, flags & ~textflags::v_title);
        return;
    }

    auto sl = wcslen(s);

    std::wstring ws(s);
    std::string str(ws.begin(), ws.end());

	if(static_cast<int>(sl) + x > m_width)
    {
        for(auto sc = 0; sc + x < m_width ; sc++)
        {
            std::wstring b;
            b+=s[sc];
            render_frame->set(sc+x, y, b, m_currentFgColor, m_currentBgColor, flags);
        }

        return;
    }

    if(x < 0)
    {
        log_info() << "x=" << x << " ax=" << std::abs(x) + 1;

        std::wstring sw(s);
        std::wstring subs = sw.substr(std::abs(x) + 1);
		for(std::size_t i=0; i<subs.length(); i++)
        {
            std::wstring b;
            b += s[i];
            render_frame->set(i, y, b, m_currentFgColor, m_currentBgColor, flags);
        }
        return;
    }

	for(std::size_t i=0; i< ws.length(); i++)
    {
        std::wstring b;
        b += ws[i];
        render_frame->set(x + i, y, b, m_currentFgColor, m_currentBgColor, flags);
    }
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_text(int x, int y, wchar_t c, int flags)
{
    std::wstring b;
    b += c;
    render_frame->set(x, y, b, m_currentFgColor, m_currentBgColor, flags);
}

void cogui::rendering_engines::ncurses_rendering_engine::set_fg_color(const color &c)
{
    m_currentFgColor = c;
}

void cogui::rendering_engines::ncurses_rendering_engine::set_bg_color(const color &c)
{
    m_currentBgColor = c;
}

void cogui::rendering_engines::ncurses_rendering_engine::set_colors(const color &fg, const color &bg)
{
    m_currentBgColor = bg;
    m_currentFgColor = fg;
}

std::string cogui::rendering_engines::ncurses_rendering_engine::name() const
{
    return "ncurses";
}

void cogui::rendering_engines::ncurses_rendering_engine::clear_area(int x, int y, int width, int height)
{
    set_fg_color(color::white);
    set_bg_color(color::black);

    console_theme* ct = dynamic_cast<console_theme*>(const_cast<theme*>(get_theme()));
    wchar_t g[2];
    g[0] = ct->get_desktop_background();
    g[1] = L'\0';
    for(int rc = y; rc <= y + height; rc++)
    {
        draw_text(x, rc, cogui::utils::repeated(width, g));
    }
}

bool cogui::rendering_engines::ncurses_rendering_engine::start_rendering()
{
    present_scene();
    swap_buffers();

    return true;
}

void cogui::rendering_engines::ncurses_rendering_engine::swap_buffers(){
    currentFrame ^= 1;
    render_frame = buffers[currentFrame ^ 1];
    presentation_frame = buffers[currentFrame];
}

void cogui::rendering_engines::ncurses_rendering_engine::present_scene()
{
    if (m_renderCallback != nullptr)
    {
        // Start the thread using a lambda to call the thread_met function
        std::thread thread1([this]() {
            std::lock_guard<std::mutex> lock(renderMutex); // Lock the mutex for the duration of this scope

            m_renderCallback();
        });

        presentation_frame->print();
        thread1.join();

        // Wait for the thread to finish
    }
}

void cogui::rendering_engines::ncurses_rendering_engine::set_rendering_function(std::function<bool ()> rendercb)
{
    m_renderCallback = rendercb;
}

void cogui::rendering_engines::ncurses_rendering_engine::erase_screen()
{
	::erase();
}

void cogui::rendering_engines::ncurses_rendering_engine::set_clip_area(const cogui::rect &r)
{
//    log_info() << "clip area:" << r;
    render_frame->set_clip_area(r);
    presentation_frame->set_clip_area(r);
}

void cogui::rendering_engines::ncurses_rendering_engine::refresh_screen()
{
    ::refresh();
}

void cogui::rendering_engines::ncurses_rendering_engine::clear_screen()
{
    render_frame->clear();
}

void cogui::rendering_engines::ncurses_rendering_engine::shutdown()
{
    log_info() << "Ending the ncurses rendering";
    ::curs_set(1);
    ::endwin();
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_title(int x, int y, const std::wstring &s, cogui::textflags flags)
{
    std::wstring final_title;
    wchar_t highlight_char = L'\0';
    int highlight_pos = -1;
    bool first_taken = false;

    for(std::size_t i=0; i<s.length(); i++)
    {
        if(s[i] == L'&')
        {
            i++;
            if( i< s.length() )
            {
                if( s[i] != L'&' && !first_taken)
                {
                    highlight_char = s[i];
                    highlight_pos = i - 1;
                    first_taken = true;
                }
                final_title += s[i];
            }
        }
        else
        {
            final_title += s[i];
        }
    }
    draw_text(x, y, final_title.c_str(), flags);
    if(highlight_char != L'\0')
    {
        // ad an extra space at the end, because we took away an & sign
		draw_text(x + final_title.length(), y, L' ', cogui::textflags::normal());

        draw_text(x + highlight_pos, y, highlight_char, cogui::textflags::underline() & cogui::textflags::bold());
    }
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_text(int x, int y, const wchar_t* s, cogui::textflags flags)
{
    draw_text(x, y, s, static_cast<int>(flags));
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_text(int x, int y, const std::wstring &s, cogui::textflags flags)
{
    draw_text(x, y, s.c_str(), flags);
}

int cogui::rendering_engines::ncurses_rendering_engine::get_screen_width() const {return m_width;}

int cogui::rendering_engines::ncurses_rendering_engine::get_screen_height() const {return m_height;}



void cogui::rendering_engines::frame::print()
{
    std::lock_guard<std::mutex> lock(renderMutex); // Lock the mutex to wait for the renderer to finish before printing the next phase

    log_debug() << "Printing Frame:" << (void*)this;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int index = (width * i) + j;
            int a =  (fg_colors[index] - 1) << 8 | (bg_colors[index] - 1);
            //log_info() << "fg_colors:" << fg_colors[index] << " bg_colors:" << bg_colors[index] << " a=" << a << " CP:" << COLOR_PAIR(a);

            const auto cp = colorpairs.at(a);

            attron(attrs[index] | COLOR_PAIR(std::get<0>(cp)));
            mvaddstr(i, j, utils::unicode_to_utf8(data[index]));
            attroff(attrs[index] | COLOR_PAIR(std::get<0>(cp)));
        }
    }

#define SOFTMOUSE 1
#if SOFTMOUSE
    int mx = mouse::get().x();
    int my = mouse::get().y();

    if(my > -1 && mx > -1 && mx < width && my < width)
    {
        log_debug() << "Mouse at:" << mx << "," << my << " - rect:" << width << "x" << height;
        int mouseIndex = (width * my) + mx;
        int a =  (fg_colors[mouseIndex] - 1) << 8 | (bg_colors[mouseIndex] - 1);

        const auto cp = colorpairs.at(a);
        attron(A_REVERSE | COLOR_PAIR(std::get<0>(cp)));
        mvaddstr(my, mx, utils::unicode_to_utf8(data[mouseIndex]));
        attroff(A_REVERSE | COLOR_PAIR(std::get<0>(cp)));

        // debug
        /*
        std::stringstream ss;
        ss << "attrs:";
        for(int i = mx; i < width; i++)
        {
            int index = (width * my) + i;

            ss << "x:" << i << " attr:" << attrs[index] << " F:" << (int)fg_colors[index] << " B:" << (int)bg_colors[index];
            ss << std::endl;

        }

        log_debug() << ss.str();
        */

    }
#endif

}


namespace cogui {
namespace rendering_engines {
WINDOW *ncurses_rendering_engine::getStdscr() const
{
    return stdscr;
}

}
}
