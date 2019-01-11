#ifndef THEME_H
#define THEME_H

#include <wchar.h>
#include <string>

namespace cogui
{

class window;

class theme
{
public:

    void draw_window(const window& w);

    // the line characters
    std::wstring UL_CORNER = L"\x2554";
    std::wstring UR_CORNER = L"\x2557";
    std::wstring LL_CORNER = L"\x255A";
    std::wstring LR_CORNER = L"\x255D";
    std::wstring HORZ_LINE = L"\x2550";
    std::wstring VERT_LINE = L"\x2551";

    // if the window is resizeable this is the corner of it
    std::wstring LR_RESIZE = L"\x251B";

    // the close button of the theme
    std::wstring WND_CLOSE = L"\x2561\x2613\x255e";
    std::wstring WND_MAXIMIZE = L"\x2561\x25ab\x255e";

    // the system menu
    std::wstring WND_SYSMENU =  L"\x2561\x25bf\x255e";

    // the delimiters of the title
    std::wstring WND_TITLE_DELIM_LEFT = L"\x2563 ";
    std::wstring WND_TITLE_DELIM_RIGHT = L" \x2560";

};
}

#endif // THEME_H
