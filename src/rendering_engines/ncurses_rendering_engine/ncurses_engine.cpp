#define _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE 600

#define MAX_DESKTOP_SIZE 4096

#include "ncurses_rendering_engine.h"
#include "events.h"
#include "mouse.h"
#include "cogui.h"
#include "desktop.h"

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
        m_colours = true;
    }

    // initialize the colorpairs
    for(const auto& cp : colorpairs)
    {
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
            rframe->set(sc+x, y, b, m_currentFgColor, m_currentBgColor, flags);
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
            rframe->set(i, y, b, m_currentFgColor, m_currentBgColor, flags);
        }
        return;
    }

	for(std::size_t i=0; i< ws.length(); i++)
    {
        std::wstring b;
        b += ws[i];
        rframe->set(x + i, y, b, m_currentFgColor, m_currentBgColor, flags);
    }
}

void cogui::rendering_engines::ncurses_rendering_engine::draw_text(int x, int y, wchar_t c, int flags)
{
    std::wstring b;
    b += c;
    rframe->set(x, y, b, m_currentFgColor,
                m_currentBgColor, flags);
    //mvwaddch(stdscr, y, x, c | flags);
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
    for(int rc = y; rc <= y + height; rc++)
    {
        draw_text(x, rc, cogui::utils::repeated(width, L" "));
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
    rframe = buffers[currentFrame ^ 1];
    pframe = buffers[currentFrame];
}

void* cogui::rendering_engines::ncurses_rendering_engine::thread_met(void* o)
{
    ((cogui::rendering_engines::ncurses_rendering_engine*)o)->m_renderCallback();
	return 0;
}

void cogui::rendering_engines::ncurses_rendering_engine::present_scene()
{
	[[maybe_unused]] int iret;
	pthread_t thread1;

	if(m_renderCallback != nullptr){
		iret = ::pthread_create( &thread1, NULL, thread_met, (void*)this);

		pframe->print();
		pthread_join( thread1, NULL);

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
//	log_info() << "clip area:" << r;
	rframe->set_clip_area(r);
	pframe->set_clip_area(r);
}

void cogui::rendering_engines::ncurses_rendering_engine::refresh_screen()
{
    ::refresh();
}

void cogui::rendering_engines::ncurses_rendering_engine::clear_screen()
{
    rframe->clear();
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

		draw_text(x + highlight_pos, y, highlight_char,
                                           cogui::textflags::underline() & cogui::textflags::bold());


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

cogui::rendering_engines::frame::frame(int w, int h)
{
    this->width = w;
    this->height = h;

    fg_colors = new uint8_t[width * height];
    bg_colors = new uint8_t[width * height];
    attrs = new int[width * height];

    data = new std::wstring[width * height];

    log_info() << "created data:" << width * height << " bytes";

    clear();
}

cogui::rendering_engines::frame::~frame()
{
    delete [] bg_colors;
    delete [] fg_colors;
    delete [] attrs;
    delete [] data;
}

void cogui::rendering_engines::frame::clear()
{
    memset(fg_colors, COLOR_WHITE, sizeof(uint8_t) * width * height);
    memset(bg_colors, COLOR_BLACK, sizeof(uint8_t) * width * height);
    memset(attrs, 0, sizeof(int) * width * height);

}

void cogui::rendering_engines::frame::set(int x, int y, std::wstring v, uint8_t fgc, uint8_t bgc, int flag)
{
	// are we inside the clip area?
	if(clip_area.height > 0 && clip_area.width > 0)
	{
		if(! (x >= clip_area.x && x <= clip_area.x + clip_area.width && y > clip_area.y && y < clip_area.y + clip_area.height)	)
		{
			return;
		}
	}


    if(x < width && y < height && x >= 0 && y >= 0)
    {
        int index = (y * width) + x;
        fg_colors[index] = fgc;
        bg_colors[index] = bgc;
        attrs[index] = flag;
        data[index] = v;
	}
}

void cogui::rendering_engines::frame::set_clip_area(const cogui::rect &r)
{
	clip_area = r;
}

extern "C" const char* unicode_to_utf8(wchar_t c)
{
    static unsigned char b_static[5];
    unsigned char* b = b_static;

    if (c<(1<<7))// 7 bit Unicode encoded as plain ascii
    {
        *b++ = (unsigned char)(c);
    }
    else if (c<(1<<11))// 11 bit Unicode encoded in 2 UTF-8 bytes
    {
        *b++ = (unsigned char)((c>>6)|0xC0);
        *b++ = (unsigned char)((c&0x3F)|0x80);
    }
    else if (c<(1<<16))// 16 bit Unicode encoded in 3 UTF-8 bytes
    {
        *b++ = (unsigned char)(((c>>12))|0xE0);
        *b++ =  (unsigned char)(((c>>6)&0x3F)|0x80);
        *b++ =  (unsigned char)((c&0x3F)|0x80);
    }

    else if (c<(1<<21))// 21 bit Unicode encoded in 4 UTF-8 bytes
    {
        *b++ = (unsigned char)(((c>>18))|0xF0);
        *b++ = (unsigned char)(((c>>12)&0x3F)|0x80);
        *b++ = (unsigned char)(((c>>6)&0x3F)|0x80);
        *b++ = (unsigned char)((c&0x3F)|0x80);
    }
    *b = '\0';
    return (const char*)b_static;
}

void cogui::rendering_engines::frame::print()
{

    int mx = mouse::get().x();
    int my = mouse::get().y();

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            int index = (width * j) + i;
            int a =  (fg_colors[index] - 1) << 8 | (bg_colors[index] - 1);

            if(mx == i && my == j)
            {
                attron(COLOR_PAIR(3));
            }
            else
            {
                attron(attrs[index] | COLOR_PAIR(a));
            }
            if(data[index].c_str())
            {
                mvaddstr(j, i, unicode_to_utf8(*data[index].c_str()));
            }
            else
            {
                if(mx == i && my == j)
                {
                    mvaddstr(j, i, " ");
                }
            }
            if(mx == i && my == j)
            {
                attroff(COLOR_PAIR(3));
            }
            else
            {
                attroff(attrs[index] | COLOR_PAIR(a));
            }
        }
    }




}


namespace cogui {
namespace rendering_engines {
WINDOW *ncurses_rendering_engine::getStdscr() const
{
    return stdscr;
}

}
}
