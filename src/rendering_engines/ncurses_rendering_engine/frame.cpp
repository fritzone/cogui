#include "frame.h"
#include "log.h"

#include <utility>
#include <cstring>

cogui::rendering_engines::frame::frame(int w, int h)
{
    log_info() << "Creating frame:" << w << "x" << h;
    this->width = w;
    this->height = h;

    fg_colors = new uint8_t[width * height];
    bg_colors = new uint8_t[width * height];
    attrs = new int[width * height];
    data = new wchar_t[width * height];

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
    log_debug() << "Setting 0 for rect:" << width << "x" << height;

    std::memset(fg_colors, 1, sizeof(uint8_t) * width * height);
    std::memset(bg_colors, 1, sizeof(uint8_t) * width * height);
    std::memset(attrs, 0, sizeof(int) * width * height);
    std::fill(data, data + width * height, L' ');
}

void cogui::rendering_engines::frame::set(int x, int y, std::wstring v, uint8_t fgc, uint8_t bgc, int flag)
{
    // log_info() << "Set at:" << x << "," << y << " v=" << v << " fgc=" << (int)fgc << " bgc=" << (int)bgc << " flag=" << flag;

    // are we inside the current clip area?
    if(clip_area.get_height() > 0 && clip_area.get_width() > 0)
    {
        if(! (x >= clip_area.get_x() && x <= clip_area.get_x() + clip_area.get_width() && y > clip_area.get_y() && y < clip_area.get_y() + clip_area.get_height())	)
        {
            return;
        }
    }

    if(x < width && y < height && x >= 0 && y >= 0 && !v.empty())
    {
        int index = (y * width) + x;
        fg_colors[index] = fgc;
        bg_colors[index] = bgc;
        attrs[index] = flag;
        data[index] = v[0];
    }
}

void cogui::rendering_engines::frame::set_clip_area(const cogui::rect &r)
{
    clip_area = r;
}
