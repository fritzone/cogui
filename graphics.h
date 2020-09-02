#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
#include <memory>

#include "cogui.h"

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

}

#endif // GRAPHICS_H
