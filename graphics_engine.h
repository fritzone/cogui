#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "cogui.h"

namespace cogui
{

class graphics_engine
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

    graphics_engine() noexcept = default;

    virtual ~graphics_engine() = default;

    virtual std::string name() const = 0;

    virtual bool initialize() = 0;
    virtual void shutdown() = 0;

    virtual void draw_text(int x, int y, wchar_t c, int flags) = 0;
    virtual void draw_text(int x, int y, const wchar_t* s, int flags) = 0;
    virtual void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags) = 0;
    virtual void draw_text(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) = 0;

    virtual void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) = 0;

    virtual void refresh_screen() = 0;
    virtual void clear_screen() = 0;

    virtual int get_screen_width() const = 0;
    virtual int get_screen_height() const = 0;

    virtual void set_fg_color(foreground_color c) = 0;
    virtual void set_bg_color(background_color c) = 0;
    virtual void set_colors(foreground_color fg, background_color bg) = 0;

};

}

#endif // GRAPHICS_H
