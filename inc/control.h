#ifndef CONTROL_H
#define CONTROL_H

#include "log.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "rect.h"
#include "string_type.h"
#include "positionable.h"

#include <string>
#include <variant>
#include <utility>
#include <memory>

namespace cogui
{

class scrollbar;
/**
 * @brief Represents a UI control element with position, size, title, and state management.
 *
 * The control class is a base class providing fundamental properties and actions for UI controls,
 * including position, visibility, focus, and press states. It supports drawing, resizing,
 * and other common behaviors shared by various control types.
 */
class control : public positionable<int>
{
public:

    /**
     * @brief Enum representing the focus state of the control.
     */
    enum class focus_state
    {
        focused = 1,      /**< Control is currently focused */
        not_focused = 2   /**< Control is not focused */
    };

    /**
     * @brief Enum representing the press state of the control.
     */
    enum class press_state
    {
        released,         /**< Control is in the released state */
        pressed           /**< Control is currently pressed */
    };

    /**
     * @brief Default constructor for control.
     *
     * Initializes a control without specific position, size, or title.
     */
    control() = default;

    /**
     * @brief Constructs a control with specified position and size.
     *
     * @param x The x-coordinate of the control's position.
     * @param y The y-coordinate of the control's position.
     * @param width The width of the control.
     * @param height The height of the control.
     */
    control(int x, int y, int width, int height);

    /**
     * @brief Constructs a control with specified position, size, and title.
     *
     * @tparam S Type of the title, expected to satisfy StringType.
     * @param x The x-coordinate of the control's position.
     * @param y The y-coordinate of the control's position.
     * @param width The width of the control.
     * @param height The height of the control.
     * @param title The title text of the control.
     */
    template<StringType S>
    control(int x, int y, int width, int height, const S& title) : control(x, y, width, height)
    {
        build(title);
    }

    /**
     * @brief Virtual destructor for control.
     */
    virtual ~control() = default;

    /**
     * @brief Sets the bounds of the control, updating its position and size.
     *
     * @param x The new x-coordinate.
     * @param y The new y-coordinate.
     * @param w The new width.
     * @param h The new height.
     */
    void set_bounds(int x, int y, int w, int h);

    /**
     * @brief Gets the bounding rectangle of the control.
     *
     * @return The bounding rectangle as a rect object.
     */
    rect get_rect() const;

    /**
     * @brief Gets the width of the control.
     *
     * @return The width as an integer.
     */
    int get_width() const;

    /**
     * @brief Sets the width of the control.
     *
     * @param width The width to set.
     */
    void set_width(int width);

    /**
     * @brief Gets the height of the control.
     *
     * @return The height as an integer.
     */
    int get_height() const;

    /**
     * @brief Sets the height of the control.
     *
     * @param height The height to set.
     */
    void set_height(int height);

    /**
     * @brief Gets the title of the control.
     *
     * @return The title as a wide string.
     */
    std::wstring get_title() const;

    /**
     * @brief Sets the title of the control.
     *
     * @param title The title to set as a wide string.
     */
    void set_title(const std::wstring &title);

    /**
     * @brief Clears the contents of the control's display area.
     */
    void clear() const;

    /**
     * @brief Gets the parent control.
     *
     * @return Pointer to the parent control, or nullptr if none.
     */
    control *get_parent() const;

    /**
     * @brief Sets the parent control.
     *
     * @param value Pointer to the parent control.
     */
    void set_parent(control *value);

    /**
     * @brief Sets focus to the control.
     */
    void focus();

    /**
     * @brief Removes focus from the control.
     */
    void unfocus();

    /**
     * @brief Checks if the control currently has focus.
     *
     * @return True if the control has focus, false otherwise.
     */
    bool has_focus() const;

    /**
     * @brief Shows the control.
     */
    void show();

    /**
     * @brief Hides the control.
     */
    void hide();

    /**
     * @brief Checks if the control is visible.
     *
     * @return True if the control is visible, false otherwise.
     */
    bool is_visible() const;

    /**
     * @brief Gets the current focus state of the control.
     *
     * @return The current focus state.
     */
    focus_state get_focus_state() const;

    /**
     * @brief Sets the focus state of the control.
     *
     * @param focus_state The focus state to set.
     */
    void set_focus_state(const focus_state &focus_state);

    /**
     * @brief Presses the control, changing its state to pressed.
     */
    void press();

    /**
     * @brief Releases the control, changing its state to released.
     */
    void release();

    /**
     * @brief Checks if the control is currently pressed.
     *
     * @return True if the control is pressed, false otherwise.
     */
    bool is_pressed() const;

    /**
     * @brief Gets the current press state of the control.
     *
     * @return The current press state.
     */
    press_state get_press_state() const;

    /**
     * @brief Sets the press state of the control.
     *
     * @param s The press state to set.
     */
    void set_press_state(press_state s);

    /**
     * @brief Gets the horizontal scrollbar associated with the control.
     *
     * @return Reference to the horizontal scrollbar.
     */
    const scrollbar &get_horizontal_scrollbar() const;

    /**
     * @brief Gets the vertical scrollbar associated with the control.
     *
     * @return Reference to the vertical scrollbar.
     */
    const scrollbar& get_vertical_scrollbar() const;

    /**
     * @brief get_y returns the Y value of this control, adjusted to the container it is in
     * @return the Y value of this control, adjusted to the container it is in
     */
    virtual int get_y() const override;

    /**
     * @brief get_x returns the X value of this control, adjusted to the container it is in
     * @return the X value of this control, adjusted to the container it is in
     */
    virtual int get_x() const override;

    /**
     * @brief Determines the first row available for content.
     *
     * Adjusts for elements like a menu, leaving space as needed for consistent layout.
     *
     * @return The first row available for content.
     */
    virtual int first_available_row() const;

    /**
     * @brief Redraws the control.
     *
     * Updates the control's display to reflect any changes in its properties or content.
     */
    virtual void redraw();

    /**
     * @brief Handles a double-click event at the specified coordinates.
     *
     * @param x The x-coordinate of the click.
     * @param y The y-coordinate of the click.
     */
    virtual void doubleclick(int x, int y);

    /**
     * @brief Handles a mouse-down event on the scrollbar.
     *
     * @param x The x-coordinate of the mouse event.
     * @param y The y-coordinate of the mouse event.
     * @return True if the event was handled, false otherwise.
     */
    virtual bool deal_with_scrollbar_mouse_down(int x, int y);

    /**
     * @brief Checks if a given point is inside the control's bounds.
     *
     * @param x The x-coordinate to check.
     * @param y The y-coordinate to check.
     * @return True if the point is inside, false otherwise.
     */
    virtual bool inside(int x, int y) const;

    /**
     * @brief Draws the control.
     *
     * Renders the control on the display. Pure virtual function to be implemented by derived classes.
     */
    virtual void draw() const = 0;

    /**
     * @brief Gets the minimum width required to render the control.
     *
     * @return The minimum drawable width.
     */
    virtual int minimum_drawable_width() const = 0;

    /**
     * @brief Gets the minimum height required to render the control.
     *
     * @return The minimum drawable height.
     */
    virtual int minimum_drawable_height() const = 0;

    /**
     * @brief Handles a click event at the specified coordinates.
     *
     * @param x The x-coordinate of the click.
     * @param y The y-coordinate of the click.
     */
    virtual void click(int x, int y) = 0;

protected:

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
    control(const control&) = delete;
    control(control&&) = delete;
    control& operator = (const control&) = delete;
    control& operator = (control&&) = delete;


    template<cogui::StringType S>
    void build(const S& title)
    {
        m_title = convert_title(title);
    }

private:
	std::shared_ptr<cogui::scrollbar> mouse_down_on_scrollbar_decrease(int x, int y); // returns the scrollbar which captures the mouse on the decrease button if any
    std::shared_ptr<cogui::scrollbar> mouse_down_on_scrollbar_increase(int x, int y); // returns the scrollbar which captures the mouse on the increase button if any
    std::shared_ptr<cogui::scrollbar> mouse_down_on_scrollbar_midportion(int x, int y); // returns the scrollbar which captures the mouse somewhere, not on the handle
};

}

#endif // CONTROL_H
