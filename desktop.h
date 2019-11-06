#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>
#include <memory>
#include <vector>

namespace cogui {

class graphics;
class theme;
class window;
class input;
class menu;

class desktop
{
public:
    void handle_mouse_move(int x, int y);

    void handle_mouse_left_click(int x, int y);
    void handle_mouse_left_down(int x, int y);
    void handle_mouse_left_up(int x, int y);

    void handle_mouse_right_down(int x, int y);
    void handle_mouse_right_up(int x, int y);


    void handle_tab();

    std::shared_ptr<theme> getTheme() const;
    std::shared_ptr<graphics> getGraphics() const;
    std::shared_ptr<input> getInput() const;

    void add_window(window* w);
    void remove_window(window* w);

    void refresh();
    void shutdown();
    void resize();
    int getWidth() const;
    int getHeight() const;

public:

    static desktop& get();

    std::vector<window *> windows() const;

private:

    desktop();
    bool initialize();

    std::shared_ptr<cogui::theme> m_theme;
    std::shared_ptr<cogui::graphics> m_graphics;
    std::shared_ptr<cogui::input> m_input;

    std::vector<window*> m_windows;
    window* m_captured_window = nullptr;
    bool m_initialized = false;
};

}

#endif // DESKTOP_H
