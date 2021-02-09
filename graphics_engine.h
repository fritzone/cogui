#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "cogui.h"

namespace cogui
{

class textflags
{
public:
    enum value : uint64_t
    {
        v_normal = 0,
        v_bold = 1 << 9,
        v_underline = 1 << 13
    };

    static textflags normal;
    static textflags bold;
    static textflags underline;

    textflags() = default;

    textflags(value a) : m_value(a) { }
    textflags(int a) : m_value(a) { }

    int operator &(const textflags& o) const;

    operator int() const;

private:
    int m_value;
};

class graphics_engine
{
public:

    static const char* type;
    static const char* path;

    enum class color : uint8_t
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
    virtual void swapBuffers() = 0;
    virtual void present_scene() = 0;
    virtual void setRenderCB(bool(*rendercb)()) = 0;

    virtual void draw_text(int x, int y, wchar_t c, int flags) = 0;
    virtual void draw_text(int x, int y, const wchar_t* s, int flags) = 0;
    virtual void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags) = 0;
    virtual void draw_text(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) = 0;

    virtual void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) = 0;

    virtual void refresh_screen() = 0;
    virtual void clear_screen() = 0;
    virtual void erase_screen() = 0;

    virtual void clear_area(int x, int y, int width, int height) = 0;

    virtual int get_screen_width() const = 0;
    virtual int get_screen_height() const = 0;

    virtual void set_fg_color(foreground_color c) = 0;
    virtual void set_bg_color(background_color c) = 0;
    virtual void set_colors(foreground_color fg, background_color bg) = 0;

};

}

#endif // GRAPHICS_H
