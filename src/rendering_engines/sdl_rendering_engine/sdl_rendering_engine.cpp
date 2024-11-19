#include "sdl_rendering_engine.h"

namespace cogui {

namespace rendering_engines {

void cogui::rendering_engines::sdl_rendering_engine::set_clip_area(const rect &r)
{

}

cogui::rendering_engines::sdl_rendering_engine::~sdl_rendering_engine()
{

}

bool cogui::rendering_engines::sdl_rendering_engine::initialize()
{

}

void cogui::rendering_engines::sdl_rendering_engine::shutdown()
{

}

void cogui::rendering_engines::sdl_rendering_engine::draw_text(int x, int y, wchar_t c, int flags)
{

}

void cogui::rendering_engines::sdl_rendering_engine::draw_text(int x, int y, const wchar_t *s, textflags flags)
{

}

void cogui::rendering_engines::sdl_rendering_engine::refresh_screen()
{

}

void cogui::rendering_engines::sdl_rendering_engine::clear_screen()
{

}

int cogui::rendering_engines::sdl_rendering_engine::get_screen_width() const
{

}

int cogui::rendering_engines::sdl_rendering_engine::get_screen_height() const
{

}

void cogui::rendering_engines::sdl_rendering_engine::set_fg_color(const color &c)
{

}

void cogui::rendering_engines::sdl_rendering_engine::set_bg_color(const color &c)
{

}

void cogui::rendering_engines::sdl_rendering_engine::set_colors(const color &fg, const color &bg)
{

}

std::string cogui::rendering_engines::sdl_rendering_engine::name() const
{

}

void cogui::rendering_engines::sdl_rendering_engine::clear_area(int x, int y, int width, int height)
{

}

bool cogui::rendering_engines::sdl_rendering_engine::start_rendering()
{

}

void cogui::rendering_engines::sdl_rendering_engine::swap_buffers()
{

}

void cogui::rendering_engines::sdl_rendering_engine::present_scene()
{

}

void cogui::rendering_engines::sdl_rendering_engine::set_rendering_function(std::function<bool ()> rendercb)
{

}

void cogui::rendering_engines::sdl_rendering_engine::erase_screen()
{

}

void cogui::rendering_engines::sdl_rendering_engine::draw_text(int x, int y, const wchar_t *s, int flags)
{

}

void cogui::rendering_engines::sdl_rendering_engine::draw_text(int x, int y, const std::wstring &s, textflags flags)
{

}

void cogui::rendering_engines::sdl_rendering_engine::draw_title(int x, int y, const std::wstring &s, textflags flags)
{

}

}
}
