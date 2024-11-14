#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <utility>

namespace cogui
{
template<typename T>
struct positionable
{

    positionable() = default;
    virtual ~positionable() = default;

    /**
     * @brief Constructs a positionable object with specified coordinates.
     *
     * @param x The initial x-coordinate.
     * @param y The initial y-coordinate.
     */
    positionable(T x, T y) : m_x(x), m_y(y) {}

    /**
     * @brief Gets the x-coordinate of the control's position.
     *
     * @return The x-coordinate as a value of type T.
     */
    virtual T get_x() const
    {
        return m_x;
    }

    /**
     * @brief Sets the x-coordinate of the control's position.
     *
     * @param x The x-coordinate to set.
     */
    void set_x(T x)
    {
        m_x = x;
    }

    /**
     * @brief Gets the y-coordinate of the control's position.
     *
     * @return The y-coordinate as a value of type T.
     */
    virtual T get_y() const
    {
        return m_y;
    }

    /**
     * @brief Sets the y-coordinate of the control's position.
     *
     * @param y The y-coordinate to set.
     */
    void set_y(T y)
    {
        m_y = y;
    }

    /**
     * @brief Sets the position of the control.
     *
     * @param x The x-coordinate to set.
     * @param y The y-coordinate to set.
     */
    void set_position(T x, T y)
    {
        m_x = x;
        m_y = y;
    }

    /**
     * @brief Gets the position of the control as a pair of coordinates.
     *
     * @return A std::pair containing the x and y coordinates.
     */
    std::pair<T, T> get_position() const
    {
        return {m_x, m_y};
    }

    /**
     * @brief Moves the rectangle by a specified offset.
     *
     * @param dx The offset to move in the x-direction.
     * @param dy The offset to move in the y-direction.
     */
    void move(T dx, T dy)
    {
        m_x += dx;
        m_y += dy;
    }

protected:

    T m_x = T{}; ///< The x-coordinate of the control's position.
    T m_y = T{}; ///< The y-coordinate of the control's position.
};


}

#endif // POSITIONABLE_H
