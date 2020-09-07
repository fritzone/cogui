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

    graphics() noexcept;
    virtual ~graphics();

    bool initialize();
    void draw(int x, int y, const wchar_t* s, int flags);
    void refresh_screen();
    void clear_screen();
    void handle_mouse_movement();
    void shutdown();
    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}
    void draw(int x, int y, wchar_t c, int flags);
    void setFgColor(color c);
    void setBgColor(color c);
    void setColors(color fg, color bg);
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


template <class T>
T repeat(T str, const std::size_t n)
{
    if (n == 0) {
    str.clear();
    str.shrink_to_fit();
    return str;
    }

    if (n == 1 || str.empty()) return str;

    const auto period = str.size();

    if (period == 1) {
    str.append(n - 1, str.front());
    return str;
    }

    str.reserve(period * n);

    std::size_t m {2};

    for (; m < n; m *= 2) str += str;

    str.append(str.c_str(), (n - (m / 2)) * period);

    return str;
}

template <typename S, typename T, typename = std::enable_if<std::is_integral<T>::value> >
S operator*(S str, const T n)
{
    return repeat(std::move(str), static_cast<std::size_t>(n));
}

std::wstring line(int l, std::wstring chr);

void draw(int x, int y, const wchar_t* s, cogui::textflags flags);


void draw(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal);


void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal);

}

#endif // GRAPHICS_H
