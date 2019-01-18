#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>
#include <memory>
#include <vector>

namespace cogui {

class graphics;
class theme;
class window;

class desktop
{
public:
    bool set_chars(int x, int y, const std::wstring &s);

    void handle_mouse_move(int x, int y);

    void handle_mouse_left_click(int x, int y);
    void handle_mouse_left_down(int x, int y);
    void handle_mouse_left_up(int x, int y);

    std::shared_ptr<cogui::theme> theme() const;
    std::shared_ptr<cogui::graphics> graphics() const;
    void add_window(window* w);
    void remove_window(window* w);

public:

    static desktop& get();

private:

    desktop();
    bool initialize();

    std::shared_ptr<cogui::theme> m_theme;
    std::shared_ptr<cogui::graphics> m_graphics;

    std::vector<window*> m_windows;
    window* m_captured_window = nullptr;
};

}

#endif // DESKTOP_H
