#ifndef THEME_CURSIVE_H
#define THEME_CURSIVE_H

#include "theme.h"

#include <wchar.h>
#include <string>

namespace cogui
{

class checkbox;
class button;
class window;
class control;
class menu;

namespace themes {

/**
 * @brief The cursive class is the example class for a console based theme
 */
class cursive_theme final : public ::cogui::theme
{
    /******************************************************************************************************************/
    /*                                                      WINDOW                                                    */
    /******************************************************************************************************************/

    // the line characters of the window
    std::wstring WND_UL_CORNER = L"\x250F"; // L"\x2554";
    std::wstring WND_UR_CORNER = L"\x2513"; // L"\x2557";
    std::wstring WND_LL_CORNER = L"\x2517"; // L"\x255A";
    std::wstring WND_LR_CORNER = L"\x251B"; // L"\x255D";
    std::wstring WND_HORZ_LINE = L"\x2501"; // L"\x2550";
    std::wstring WND_VERT_LINE = L"\x2503"; // L"\x2551";

    // if there is a main menu attached to this window
    std::wstring WND_VERT_MENULINE_START =          L"\x2523"; // L"\x2520";
    std::wstring WND_VERT_MENULINE_END =            L"\x252B"; // L"\x2528";
    std::wstring WND_HORZ_MENULINE =                L"\x2500";
    std::wstring WND_VERT_MENULINE_START_RESIZE =   L"\x2523";
    std::wstring WND_VERT_MENULINE_END_RESIZE =     L"\x252B";

    // if the window is resizeable this is the corner of it
    std::wstring WND_LR_RESIZE = L"\x251B";

    // the close button of the theme
    std::wstring WND_CLOSE = L"\x252B\x2613\x2523";
    std::wstring WND_MAXIMIZE = L"\x252B\x25ab\x2523";

    // the system menu
    std::wstring WND_SYSMENU =  L"\x252B\x25bf\x2523";
    std::wstring WND_SYSMENU_DOWN =  L"\x252B\x25b5\x2523";

    // the delimiters of the title
    std::wstring WND_TITLE_DELIM_LEFT = L"\x252B ";
    std::wstring WND_TITLE_DELIM_RIGHT = L" \x2523";

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
    std::wstring MNU_LEFT_SEPARATOR = L"\x251c";
    std::wstring MNU_RIGHT_SEPARATOR = L"\x2524";
    std::wstring MNU_EMPTY_CHAR = L"\x2800";
    /******************************************************************************************************************/
    /*                                                    CHECKBOX                                                    */
    /******************************************************************************************************************/

    std::wstring CHK_UNCHECKED = L"\x2610"; // unchecked checkbox
	std::wstring CHK_CHECKED = L"\x2611"; // checked checkbox

	/******************************************************************************************************************/
	/*                                                    RADIO BUTTON                                                */
	/******************************************************************************************************************/

	std::wstring RDB_UNSELECTED = L"\x2B58"; // unselected radiobutton
	std::wstring RDB_SELECTED = L"\x2B57"; // selected radio



    /******************************************************************************************************************/
    /*                                                    SCROLLBAR                                                   */
    /******************************************************************************************************************/
    std::wstring SCROLL_UP_ARROW = L"\x2353";
    std::wstring SCROLL_DOWN_ARROW = L"\x234c";
    std::wstring SCROLL_VERTICAL_BODY = L"\x2502";
    std::wstring SCROLL_VERTICAL_HANDLE = L"\x233c";
    std::wstring SCROLL_LEFT_ARROW = L"\x2343";
    std::wstring SCROLL_RIGHT_ARROW = L"\x2344";
    std::wstring SCROLL_HORIZONTAL_BODY = L"\x2500";
    std::wstring SCROLL_HORIZONTAL_HANDLE = L"\x233c";


public:

    cursive_theme() = default;
    ~cursive_theme() override = default;

    void clear(const control& c) override;

    void draw_window(const window& w) override;
    void draw_button(const button& b) override;
    void draw_menu(const menu &m) override;
    void draw_checkbox(const checkbox& c) override;
    void draw_scrollbar(const scrollbar &s) override;
	void draw_radiobutton(const radiobutton& rb) override;
	void draw_radiobutton_group(const radiobutton_group& rbg) override;


    int minimum_checkbox_width(const checkbox& c) override;
    int minimum_checkbox_height(const checkbox& c) override;

    int minimum_button_width(const button& b) override;
    int minimum_button_height(const button& b) override;

    int minimum_window_width(const window& w) override;
    int minimum_window_height(const window& w) override;

	int minimum_radiobutton_width(const radiobutton& r) override;
	int minimum_radiobutton_height(const radiobutton& r) override;

	int minimum_radiobutton_group_width(const radiobutton_group& c) override;
	int minimum_radiobutton_group_height(const radiobutton_group& c) override;

    int first_available_row(const window& w) override;

    std::string name() override;
private:

    void draw_horizontal_scrollbar(control* c, scrollbar& s);
    void draw_verticall_scrollbar(control* c, scrollbar& s);

private:


};
}
}

#endif // THEME_H
