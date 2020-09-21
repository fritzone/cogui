#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
#include <memory>

#include "cogui.h"
#include "desktop.h"

// hmm, maybe we should include the cursed headers
typedef struct _win_st WINDOW;

namespace cogui
{

class graphics
{
public:

    enum class color
    {
        black = 1,
        red = 2,
        green = 3,
        yellow = 4,
        blue = 5,
        magenta = 6,
        cyan = 7,
        white = 8
    };

    using foreground_color = color;
    using background_color = color;

    graphics() noexcept;
    virtual ~graphics();

    bool initialize();
    void shutdown();

    void draw_text(int x, int y, wchar_t c, int flags);
    void draw_text(int x, int y, const wchar_t* s, int flags);
    void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags);
    void draw_text(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal);

    void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal);

    void refresh_screen();
    void clear_screen();

    int get_screen_width() const {return m_width;}
    int get_screen_height() const {return m_height;}

    void set_fg_color(foreground_color c);
    void set_bg_color(background_color c);
    void set_colors(foreground_color fg, background_color bg);
private:
    WINDOW *stdscr = nullptr;
    int m_width = -1;
    int m_height = -1;
    bool m_colours = false;
    color m_currentFgColor = color::white;
    color m_currentBgColor = color::black;

    void turnoff_current_color();
    void turnon_current_color();
};




}

#endif // GRAPHICS_H
