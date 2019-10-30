#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
#include <memory>

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
    void draw(int x, int y, const wchar_t* s);
    void refresh_screen();
    void handle_mouse_movement();
    void shutdown();
    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}
private:
    WINDOW *stdscr = nullptr;
    int m_width = -1;
    int m_height = -1;
    bool m_colours = false;
};

}

#endif // GRAPHICS_H
