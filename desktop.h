#ifndef DESKTOP_H
#define DESKTOP_H

#include "events.h"

#include <string>
#include <memory>
#include <vector>

namespace cogui {

class graphics_engine;
class theme;
class window;
class input;
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

    std::shared_ptr<theme> getTheme() const;
    std::shared_ptr<graphics_engine> getGraphics() const;
    std::shared_ptr<input> getInput() const;

    void add_window(window* w);
    void remove_window(window* w);
    void maximize_window(window* w);

    void refresh();
    void clear();
    void shutdown();
    void resize();
    int getWidth() const;
    int getHeight() const;
    void redraw();

public:

    static void init(const std::string& theme_name);

    static desktop& get();

    std::vector<window *> windows() const;

private:

    desktop();
    ~desktop();
    bool initialize();

    std::shared_ptr<cogui::theme> m_theme;
    std::shared_ptr<cogui::graphics_engine> m_graphics;
    std::shared_ptr<cogui::input> m_input;

    std::vector<window*> m_windows;
    window* m_captured_window = nullptr;
    bool m_initialized = false;

    static std::string m_s_theme_name;
    static std::string m_s_graphics_engine_name;

    static bool renderer();

};

}

#endif // DESKTOP_H
