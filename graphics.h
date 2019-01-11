#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>

#include "events.h"


// hmm, maybe we should include the cursed headers
typedef struct _win_st WINDOW;

namespace cogui
{

class graphics
{
public:
    graphics();
    virtual ~graphics();

    bool initialize();
    bool set_chars(int x, int y, const std::wstring &s);
    void draw(int x, int y, const wchar_t* s);
    void refresh_screen();
    event get_next_event();
    void handle_mouse_movement();

private:
    WINDOW *stdscr;
    std::vector< std::vector<wchar_t>> chars;
    int m_width;
    int m_height;

};

}

#endif // GRAPHICS_H
