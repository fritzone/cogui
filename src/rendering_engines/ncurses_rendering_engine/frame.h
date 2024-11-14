#ifndef FRAME_H
#define FRAME_H

#include "rect.h"

#include <string>

namespace cogui {

namespace rendering_engines {

struct frame final
{
    frame(int w, int h);
    ~frame();

    void clear();

    void set(int x, int y, std::wstring v, uint8_t fgc, uint8_t bgc, int flag);
    void set_clip_area(const rect& r);
    void print();

    int width;
    int height;
    wchar_t* data;
    uint8_t* fg_colors;
    uint8_t* bg_colors;
    int* attrs;
    rect clip_area;

};

}
}
#endif // FRAME_H
