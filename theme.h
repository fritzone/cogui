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

    /* resize graphics down */

    // the line characters when moving/resizing the window
    std::wstring UL_CORNER_RESIZE = L"\x250F";
    std::wstring UR_CORNER_RESIZE = L"\x2513";
    std::wstring LL_CORNER_RESIZE = L"\x2517";
    std::wstring LR_CORNER_RESIZE = L"\x251B";
    std::wstring HORZ_LINE_RESIZE = L"\x2501";
    std::wstring VERT_LINE_RESIZE = L"\x2503";

    // the system menu, resize mode
    std::wstring WND_SYSMENU_RESIZE =  L"\x252B\x25bf\x2523";

    // the delimiters of the title
    std::wstring WND_TITLE_DELIM_LEFT_RESIZE = L"\x252B ";
    std::wstring WND_TITLE_DELIM_RIGHT_RESIZE = L" \x2523";

    // the close button of the theme
    std::wstring WND_CLOSE_RESIZE = L"\x252B\x2613\x2523";
    std::wstring WND_MAXIMIZE_RESIZE = L"\x252B\x25ab\x2523";
};
}

#endif // THEME_H
