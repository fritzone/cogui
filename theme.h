#ifndef THEME_H
#define THEME_H

#include <wchar.h>
#include <string>

namespace cogui
{

class checkbox;
class button;
class window;
class control;
class menu;

class theme
{
public:

    void clear(const control& c);

    void draw_window(const window& w);
    void draw_button(const button& b);
    void draw_menu(const menu &m);
    void draw_checkbox(const checkbox& c);

    int minimum_checkbox_width(const checkbox& c);
    int minimum_checkbox_height(const checkbox& c);

    int minimum_button_width(const button& b);
    int minimum_button_height(const button& b);

    int minimum_window_width(const window& w);
    int minimum_window_height(const window& w);

    /******************************************************************************************************************/
    /*                                                      WINDOW                                                    */
    /******************************************************************************************************************/

    // the line characters of the window
    std::wstring WND_UL_CORNER = L"\x2554";
    std::wstring WND_UR_CORNER = L"\x2557";
    std::wstring WND_LL_CORNER = L"\x255A";
    std::wstring WND_LR_CORNER = L"\x255D";
    std::wstring WND_HORZ_LINE = L"\x2550";
    std::wstring WND_VERT_LINE = L"\x2551";

    // if the window is resizeable this is the corner of it
    std::wstring WND_LR_RESIZE = L"\x251B";

    // the close button of the theme
    std::wstring WND_CLOSE = L"\x2561\x2613\x255e";
    std::wstring WND_MAXIMIZE = L"\x2561\x25ab\x255e";

    // the system menu
    std::wstring WND_SYSMENU =  L"\x2561\x25bf\x255e";

    // the delimiters of the title
    std::wstring WND_TITLE_DELIM_LEFT = L"\x2563 ";
    std::wstring WND_TITLE_DELIM_RIGHT = L" \x2560";

    /* resize graphics for windows down */

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

    /******************************************************************************************************************/
    /*                                                      BUTTON                                                    */
    /******************************************************************************************************************/

    // Normal state, button is just drawn  as it is, thin line

    std::wstring BTN_UL_CORNER_STATE_UP = L"\x250C";    // Upper left corner
    std::wstring BTN_UR_CORNER_STATE_UP = L"\x2512";    // Upper right corner
    std::wstring BTN_LL_CORNER_STATE_UP = L"\x2515";    // Lower left corner
    std::wstring BTN_LR_CORNER_STATE_UP = L"\x251B";    // Lower right corner

    std::wstring BTN_TOP_BORDER_UP = L"\x2500";    // Top border for line
    std::wstring BTN_BOTTOM_BORDER_UP = L"\x2501";    // Bottom border for line, thicker than top
    std::wstring BTN_LEFT_UP = L"\x2502";    // Left border for line
    std::wstring BTN_RIGHT_UP = L"\x2503";    // Right border for line, thicker than left

    // Pressed state, button is drawn with thicker border

    std::wstring BTN_UL_CORNER_STATE_PRESSED = L"\x250F";    // PRESSED upper left corner
    std::wstring BTN_UR_CORNER_STATE_PRESSED = L"\x2511";    // PRESSED upper right corner
    std::wstring BTN_LL_CORNER_STATE_PRESSED = L"\x2516";    // PRESSED Lower left corner
    std::wstring BTN_LR_CORNER_STATE_PRESSED = L"\x2518";    // PRESSED Lower right corner

    std::wstring BTN_TOP_BORDER_PRESSED = L"\x2501";    // PRESSED Top border for line
    std::wstring BTN_BOTTOM_BORDER_PRESSED = L"\x2500";    // PRESSED Bottom border for line
    std::wstring BTN_LEFT_PRESSED = L"\x2503";    // PRESSED Left border for line
    std::wstring BTN_RIGHT_PRESSED = L"\x2502";    // PRESSED Right border for line

    // Focused state, buttons' border is dotted
    std::wstring BTN_UL_CORNER_STATE_FOCUSED = L"\x250C";    // FOCUSED upper left corner
    std::wstring BTN_UR_CORNER_STATE_FOCUSED = L"\x2512";    // FOCUSED upper right corner
    std::wstring BTN_LL_CORNER_STATE_FOCUSED = L"\x2515";    // FOCUSED Lower left corner
    std::wstring BTN_LR_CORNER_STATE_FOCUSED = L"\x251B";    // FOCUSED Lower right corner

    std::wstring BTN_TOP_BORDER_FOCUSED = L"\x2504";    // FOCUSED Top border for line
    std::wstring BTN_BOTTOM_BORDER_FOCUSED = L"\x2505";    // FOCUSED Bottom border for line
    std::wstring BTN_LEFT_FOCUSED = L"\x250A";    // FOCUSED Left border for line
    std::wstring BTN_RIGHT_FOCUSED = L"\x250B";    // FOCUSED Right border for line, thicker

    /******************************************************************************************************************/
    /*                                                      MENU                                                      */
    /******************************************************************************************************************/

    std::wstring MNU_UL_CORNER = L"\x250C";    // Upper left corner
    std::wstring MNU_UR_CORNER = L"\x2510";    // Upper right corner
    std::wstring MNU_LL_CORNER = L"\x2514";    // Lower left corner
    std::wstring MNU_LR_CORNER = L"\x2518";    // Lower right corner
    std::wstring MNU_HORIZONTAL = L"\x2500";
    std::wstring MNU_VERTICAL = L"\x2502";
    std::wstring MNU_SYSMENU_TOP =  L"\x2502 \x2514";

    /******************************************************************************************************************/
    /*                                                    CHECKBOX                                                    */
    /******************************************************************************************************************/

    std::wstring CHK_UNCHECKED = L"\x2610"; // L"[ ]"; // L"\x2610"; // unchecked checkbox
    std::wstring CHK_CHECKED = L"\x2611"; // L"[X]"; // L"\x2611"; // unchecked checkbox

};
}

#endif // THEME_H
