#ifndef MOUSE_H
#define MOUSE_H

#include <string>

namespace cogui
{

class mouse final
{
public:

    enum class button
    {
        left,
        right,
        left_and_right,
        none
    };

    static mouse& get();

    static std::string buttonName(button);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    button buttons() const;
    void set_button(button b);
    void clear_button(button b);

    bool needs_cursor_emulation() const;
    void set_cursor_emulation(bool v)
    {
        m_needs_cursor_emulation = v;
    }

private:
    mouse();

    int m_x = -1;
    int m_y = -1;
    button m_button = button::none;
    bool m_needs_cursor_emulation = false;
};

}

#endif // MOUSE_H
