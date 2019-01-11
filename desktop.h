#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>
#include <memory>

namespace cogui {

class graphics;
class theme;

class desktop
{
public:
    bool set_chars(int x, int y, const std::wstring &s);
    void handle_mouse_left_click();
    std::shared_ptr<cogui::theme> theme() const;
    std::shared_ptr<cogui::graphics> graphics() const;

public:

    static desktop& get();

private:

    desktop();
    bool initialize();

    std::shared_ptr<cogui::theme> m_theme;
    std::shared_ptr<cogui::graphics> m_graphics;
};

}

#endif // DESKTOP_H
