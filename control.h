#ifndef CONTROL_H
#define CONTROL_H

#include "log.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

#include <string>

namespace cogui
{

class scrollbar;

class control
{
public:

    enum class focus_state
    {
        focused = 1,
        not_focused = 2
    };

    enum class press_state
    {
        released,
        pressed
    };

    control() = default;

    /**
     * @brief control creates a control at the given position and size
     *
     * @param x - the x coordinate
     * @param y - the y coordinate
     * @param width - the width of it
     * @param height - the height of it
     */
    control(int x, int y, int width, int height);

    /**
     * @brief control creates a control at the given position and size and the given title
     * as a wide string
     *
     * @param x - the x coordinate
     * @param y - the y coordinate
     * @param width - the width of it
     * @param height - the height of it
     * @param title - the title of the control
     */
    control(int x, int y, int width, int height, const std::wstring& title);

    /**
     * @brief control creates a control at the given position and size and the given title
     * as a std::string
     *
     * @param x - the x coordinate
     * @param y - the y coordinate
     * @param width - the width of it
     * @param height - the height of it
     * @param title - the title of the control
     */
    control(int x, int y, int width, int height, const std::string& title);

    /**
     * @brief a default destructor should do it
     */
    virtual ~control() = default;

    /**
     * @brief getX returns the X coordinate of the control
     * @return the X coordinate of the control
     */
    int get_x() const;

    /**
     * @brief setX sets the X coordinate of the control
     * @param x the X coordinate to set
     */
    void set_x(int x);

    /**
     * @brief getY returns the Y coordinate of the control
     * @return the Y coordinate of the control
     */
    int get_y() const;

    /**
     * @brief setY sets the Y coordinate of the control
     * @param y the Y coordinate to set
     */
    void set_y(int y);

    /**
     * @brief setBounds Will relocate the control to the given position, given size
     *
     * @param x the X coordinate
     * @param y the Y coordinate
     * @param w the width
     * @param h the height
     */
    void set_bounds(int x, int y, int w, int h);

    /**
     * @brief first_available_row will return the first row which is available to the content of the containeir to
     * draw the controls of it. For example, if there is a menu, it will return +2, in order for the content to not to
     * occupy the menu
     * @return
     */
    virtual int first_available_row() const { return 1; };

    int get_width() const;
    void set_width(int width);

    int get_height() const;
    void set_height(int height);

    std::wstring get_title() const;
    void set_title(const std::wstring &title);

    void clear() const;

    control *get_parent() const;
    void set_parent(control *value);

    void focus();
    void unfocus();
    bool has_focus() const;

    void show();
    void hide();
    bool is_visible() const;

    focus_state get_focus_state() const;
    void set_focus_state(const focus_state &focus_state);

    void press();
    void release();
    bool is_pressed() const;
    press_state get_press_state() const;
    void set_press_state(press_state s);

    const scrollbar &get_horizontal_scrollbar() const;

    const scrollbar& get_vertical_scrollbar() const;

    /**
     * @brief redraw Re-draws the control
     */
    virtual void redraw();

    virtual int minimum_drawable_width() const = 0;
    virtual int minimum_drawable_height() const = 0;
    virtual void doubleclick(int,int);
    virtual void draw() const = 0;

    virtual bool inside(int x, int y) const;
    virtual void click() = 0;

    virtual bool deal_with_scrollbar_mouse_down(int x, int y);

protected:

    int m_x = 0;
    int m_y = 0;
    int m_width = 0;
    int m_height = 0;
    std::wstring m_title = L"";
    control* m_parent = nullptr;
    focus_state m_focus_state = focus_state::not_focused;
    press_state m_state = press_state::released;

    // the location where the control is placed initially, when there was no layout applied to it
    int m_initial_x = -1, m_initial_y = -1, m_initial_width = -1, m_initial_height = -1;

    int m_minimumWidth = -1;
    int m_minimumHeight = -1;
    int m_maximumWidth = -1;
    int m_maximumHeight = -1;

    bool m_visible = true;
    std::shared_ptr<scrollbar> m_horizontal_scrollbar = nullptr;
    std::shared_ptr<scrollbar> m_vertical_scrollbar = nullptr;

private:

	/**
	 * @brief copying, moving, assigning is prohibited
	 */
//	control(const control&) = default;
//	control(control&&) = default;
//	control& operator = (const control&) = default;
//	control& operator = (control&&) = default;


private:
    std::shared_ptr<scrollbar> mouse_down_on_scrollbar_decrease(int x, int y); // returns the scrollbar which captures the mouse on the decrease button if any
    std::shared_ptr<cogui::scrollbar> mouse_down_on_scrollbar_increase(int x, int y); // returns the scrollbar which captures the mouse on the increase button if any
    std::shared_ptr<cogui::scrollbar> mouse_down_on_scrollbar_midportion(int x, int y); // returns the scrollbar which captures the mouse somewhere, not on the handle
};

}

#endif // CONTROL_H
