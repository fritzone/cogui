#ifndef NCURSES_ENGINE_H
#define NCURSES_ENGINE_H

#include <rendering_engine.h>
#include <string.h>
#include <string>

typedef struct _win_st WINDOW;

namespace cogui {

namespace rendering_engines {

struct frame;

class ncurses_rendering_engine : public rendering_engine
{
public:

    virtual ~ncurses_rendering_engine();

    bool initialize() override;
    void shutdown() override;
    void draw_text(int x, int y, wchar_t c, int flags) override;
    void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags) override;


    void refresh_screen() override;
    void clear_screen() override;
    int get_screen_width() const override;
    int get_screen_height() const override;
    void set_fg_color(const color& c) override;
    void set_bg_color(const color& c) override;
    void set_colors(const color& fg, const color& bg) override;
    std::string name() const override;
    void clear_area(int x, int y, int width, int height) override;
    bool start_rendering() override;
    void swap_buffers() override;
    void present_scene() override;
    void set_rendering_function(std::function<bool()> rendercb) override;
    void erase_screen() override;

	/**
	 * @brief set_clip_area Sets the clip area in which we can draw. Drawing outside of the clip area is not
	 * permitted, all visual artifacts going there should not be processed
	 * @param r
	 */
	virtual void set_clip_area(const rect& r) override;


    WINDOW *getStdscr() const;

private:
	std::function<bool()> m_renderCallback;
	void draw_text(int x, int y, const wchar_t* s, int flags) ;
    void draw_text(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal() );
    void draw_title(int x, int y, const std::wstring& s, cogui::textflags flags = cogui::textflags::normal() );

    WINDOW *stdscr = nullptr;
    int m_width = -1;
    int m_height = -1;
    bool m_colours = false;
    color m_currentFgColor = color::white;
    color m_currentBgColor = color::black;
    frame* presentation_frame = nullptr;
    frame* render_frame = nullptr;
    frame* buffers[2];
    int currentFrame = 0;

};
}
}

#endif // NCURSES_ENGINE_H
