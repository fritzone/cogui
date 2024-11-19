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
 * @brief The blitma class is the example class for a graphics theme
 */
class blitmap_theme final : public ::cogui::theme
{

public:

    blitmap_theme() = default;
    ~blitmap_theme() override = default;

    void clear(const control& c) override;

    void draw_window(const window& w) override;
    void draw_button(const button& b) override;
    void draw_label(const label& l) override;
    void draw_menu(const menu &m) override;
    void draw_checkbox(const checkbox& c) override;
    void draw_scrollbar(const scrollbar &s) override;
	void draw_radiobutton(const radiobutton& rb) override;
	void draw_radiobutton_group(const radiobutton_group& rbg) override;

    int minimum_checkbox_width(const checkbox& c) override;
    int minimum_checkbox_height(const checkbox& c) override;

    int minimum_label_width(const label& l) override;
    int minimum_label_height(const label& l) override;

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
