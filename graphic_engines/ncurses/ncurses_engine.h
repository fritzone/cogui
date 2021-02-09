#ifndef NCURSES_ENGINE_H
#define NCURSES_ENGINE_H

#include <graphics_engine.h>
#include <string.h>
#include <string>

typedef struct _win_st WINDOW;

namespace cogui {

namespace graphic_engines {

struct frame final
{
    frame(int w, int h);
    ~frame();

    void clear();

    void set(int x, int y, std::wstring v, uint8_t fgc, uint8_t bgc, int flag);

    void print();

    int width;
    int height;
    std::wstring* data;
    uint8_t* fg_colors;
    uint8_t* bg_colors;
    int* attrs;

};

class ncurses : public graphics_engine
{
public:

    virtual ~ncurses();

    bool initialize() override;
    void shutdown() override;
    void draw_text(int x, int y, wchar_t c, int flags) override;
    void draw_text(int x, int y, const wchar_t* s, int flags) override;
    void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags) override;
    void draw_text(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) override;
    void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal) override;
    void refresh_screen() override;
    void clear_screen() override;
    int get_screen_width() const override;
    int get_screen_height() const override;
    void set_fg_color(foreground_color c) override;
    void set_bg_color(background_color c) override;
    void set_colors(foreground_color fg, background_color bg) override;
    std::string name() const override;
    void clear_area(int x, int y, int width, int height) override;

    void swapBuffers() override;
    void present_scene() override;
    void setRenderCB(bool(*rendercb)()) override {
        renderCallback = rendercb;
    }
    void erase_screen() override;
private:
    WINDOW *stdscr = nullptr;
    int m_width = -1;
    int m_height = -1;
    bool m_colours = false;
    color m_currentFgColor = color::white;
    color m_currentBgColor = color::black;
    frame* pframe = nullptr;
    frame* rframe = nullptr;
    frame* buffers[2];
    int currentFrame = 0;
    bool(*renderCallback)();


};
}
}

#endif // NCURSES_ENGINE_H
