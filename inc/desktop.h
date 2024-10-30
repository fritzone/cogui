#ifndef DESKTOP_H
#define DESKTOP_H

#include "events.h"

#include <string>
#include <memory>
#include <vector>

namespace cogui {

class rendering_engine;
class theme;
class window;
class input_provider;
class menu;

class desktop
{
public:
    bool handle_mouse_move(int x, int y);

    bool handle_mouse_left_click(int x, int y);
    bool handle_mouse_left_down(int x, int y);
    bool handle_mouse_left_up(int x, int y);

    bool handle_mouse_right_down(int x, int y);
    bool handle_mouse_right_up(int x, int y);

    bool handle_mouse_doubleclick(int x, int y);

    void handle_tab();

    bool handle_key(std::shared_ptr<cogui::events::keypress> k);

	std::shared_ptr<theme> get_theme() const;
	std::shared_ptr<rendering_engine> get_graphics() const;
	std::shared_ptr<input_provider> get_input() const;
	const std::vector<window *>& get_windows() const;
	int get_width() const;
	int get_height() const;

    void add_window(window* w);
    void remove_window(window* w);
    void maximize_window(window* w);

    void refresh();
    void clear();
    void shutdown();
    void resize();
    void redraw();


public:

    static void init(const std::string& theme_name);
    static desktop& get();

private:

    desktop();
    ~desktop();
    bool initialize();

    std::shared_ptr<cogui::theme> m_theme;
    std::shared_ptr<cogui::rendering_engine> m_rendering_engine;
	std::shared_ptr<cogui::input_provider> m_input;

    std::vector<window*> m_windows;
    window* m_captured_window = nullptr;
    bool m_initialized = false;

    static bool renderer();

};

}

#endif // DESKTOP_H
