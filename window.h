#ifndef WINDOW_H
#define WINDOW_H

#include "control.h"

#include <string>

namespace cogui
{

class window : public control
{
public:

    // which state the window currently is in, used for drawing.
    enum class draw_state
    {
        normal,
        resizing,
        moving
    };

    /**
     * Will create a window on the current screen.
     * @param x,y - the start position of the windows
     * @param w,h - the width and height of the windows
     */
    window(int x, int y, int width, int height);
    ~window() override;

    void draw() const override;

    /* mouse related */
    void click(int x, int y);
    void mouse_move(int x, int y);
    void left_mouse_down(int x, int y);
    void left_mouse_up(int x, int y);

    std::wstring title() const;
    void setTitle(const std::wstring &title);

    bool resizeable() const;
    void setResizeable(bool resizeable);

    bool hasCloseButton() const;
    void setHasCloseButton(bool hasCloseButton);

    bool hasMaximizeButton() const;
    void setHasMaximizeButton(bool hasMaximizeButton);

    bool hasSysmenuButton() const;
    void setHasSysmenuButton(bool hasSysmenuButton);

    draw_state getDrawState() const;
    virtual bool inside(int x, int y) const override;
private:

    std::wstring m_title;
    bool m_resizeable = true;
    bool m_hasCloseButton = true;
    bool m_hasMaximizeButton = true;
    bool m_hasSysmenuButton = true;
    draw_state m_draw_state = draw_state::normal;
    int m_mouse_down_x = -1;
    int m_mouse_down_y = -1;
    int m_prev_w = -1;
    int m_prev_h = -1;
};

}

#endif // WINDOW_H
