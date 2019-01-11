#ifndef WINDOW_H
#define WINDOW_H

#include "control.h"

#include <string>

namespace cogui
{

class window : public control
{
public:

    /**
     * Will create a window on the current screen.
     * @param x,y - the start position of the windows
     * @param w,h - the width and height of the windows
     */
    window(int x, int y, int width, int height);

    void draw() const;

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

private:

    std::wstring m_title;
    bool m_resizeable = true;
    bool m_hasCloseButton = true;
    bool m_hasMaximizeButton = true;
    bool m_hasSysmenuButton = true;
};

}

#endif // WINDOW_H
