#ifndef THEME_H
#define THEME_H

#include "cogui.h"

namespace cogui
{

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
    virtual int minimum_checkbox_width(const checkbox& c) = 0;
    virtual int minimum_checkbox_height(const checkbox& c) = 0;
    virtual int minimum_button_width(const button& b) = 0;
    virtual int minimum_button_height(const button& b) = 0;
    virtual int minimum_window_width(const window& w) = 0;
    virtual int minimum_window_height(const window& w) = 0;

    virtual std::string name() = 0;
};

}


#endif // THEME_H
