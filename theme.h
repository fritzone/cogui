#ifndef THEME_H
#define THEME_H

#include <string>
#include <tuple>
#include <map>

#include "rect.h"

namespace cogui
{

class menu;
class control;
class window;
class button;
class scrollbar;
class checkbox;

class theme
{
public:

    static const char* type;
    static const char* path;

    theme() {}
    virtual ~theme() {}

    /**
     * @brief clear
     * @param c
     */
    virtual void clear(const control& c) = 0;
    virtual void draw_window(const window& w) = 0;
    virtual void draw_button(const button& b) = 0;
    virtual void draw_menu(const menu &m) = 0;
    virtual void draw_checkbox(const checkbox& c) = 0;
    virtual void draw_scrollbar(const scrollbar& s) = 0;
    virtual int minimum_checkbox_width(const checkbox& c) = 0;
    virtual int minimum_checkbox_height(const checkbox& c) = 0;
    virtual int minimum_button_width(const button& b) = 0;
    virtual int minimum_button_height(const button& b) = 0;
    virtual int minimum_window_width(const window& w) = 0;
    virtual int minimum_window_height(const window& w) = 0;
    virtual int first_available_row(const window& w) = 0;

    virtual std::string name() = 0;


	virtual cogui::rect close_button_pos(const cogui::window &w);

	virtual cogui::rect sysmenu_button_pos(const cogui::window &w);

	virtual cogui::rect maximize_button_pos(const cogui::window &w);

	virtual void update_menubar_positions(cogui::menu *m, std::pair<int, int> ul, std::pair<int, int> lr);


	virtual bool current_menu_position_stored(const cogui::menu &m);

	virtual cogui::rect current_menu_position(const cogui::menu &m);

	virtual void set_window_close_button_position(const window& w, const rect& r);

	virtual void set_window_sysmenu_button_position(const window& w, const rect& r);

	virtual void set_window_maximize_button_position(const window& w, const rect& r);

	virtual std::tuple<menu*, rect> menu_at(int x, int y);


private:

	std::map<const window*, rect> m_close_button_positions;
	std::map<const window*, rect> m_sysmenu_button_positions;
	std::map<const window*, rect> m_maximize_button_positions;

	// this will hold the positions where the menu was drawn
	// key is the menu, followed by two coordinates on the screen, upper left, lower right corner
	std::map<menu*, rect> m_menu_positions;
};

}


#endif // THEME_H
