#ifndef CONTROL_H
#define CONTROL_H

#include "log.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

#include <string>

namespace cogui
{

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
     * @brief copying, moving, assigneing is deleted
     */
    control(const control&) = delete;
    control(control&&) = delete;
    control& operator = (const control&) = delete;
    control& operator = (control&&) = delete;

    /**
     * @brief a default destructor should do it
     */
    virtual ~control() = default;

    /**
     * @brief getX returns the X coordinate of the control
     * @return the X coordinate of the control
     */
    int getX() const;

    /**
     * @brief setX sets the X coordinate of the control
     * @param x the X coordinate to set
     */
    void setX(int x);

    /**
     * @brief getY returns the Y coordinate of the control
     * @return the Y coordinate of the control
     */
    int getY() const;

    /**
     * @brief setY sets the Y coordinate of the control
     * @param y the Y coordinate to set
     */
    void setY(int y);

    int getWidth() const;
    void setWidth(int width);

    int getHeight() const;
    void setHeight(int height);

    std::wstring getTitle() const;
    void setTitle(const std::wstring &title);

    void clear() const;

    control *getParent() const;
    void setParent(control *value);

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

    /**
     * @brief redraw Re-draws the control
     */
    virtual void redraw();

    virtual int minimumDrawableWidth() const = 0;
    virtual int minimumDrawableHeight() const = 0;
    virtual void click() = 0;
    virtual void doubleclick(int,int);
    virtual void draw() const = 0;
    virtual bool inside(int x, int y) const;

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

private:
    void initInitialPosition();
};

}

#endif // CONTROL_H
