#ifndef RECT_H
#define RECT_H

#include "positionable.h"

namespace cogui {

/**
 * @class rect
 * @brief Represents a rectangular area in a 2D coordinate space.
 *
 * This class provides functionality to define and manipulate a rectangle.
 * It includes methods to determine whether a point lies within the rectangle,
 * both inclusive and exclusive of borders, along with common operations like resizing and moving.
 */
struct rect : positionable<int>
{
    /**
     * @brief Default constructor. Initializes the rectangle with an invalid size (-1, -1).
     */
    rect() = default;

    /**
     * @brief Parameterized constructor. Initializes the rectangle with specified coordinates and dimensions.
     *
     * @param x The x-coordinate of the top-left corner of the rectangle.
     * @param y The y-coordinate of the top-left corner of the rectangle.
     * @param m_width The m_width of the rectangle.
     * @param m_height The m_height of the rectangle.
     */
    rect(int x, int y, int width, int height) : positionable<int>(x, y), m_width(width), m_height(height)
    {}

    /**
     * @brief get_width returns the width of the rect
     * @return the width of the rect
     */
    int get_width() const
    {
        return m_width;
    }

    /**
     * @brief get_height returns the height of the rect
     * @return the height of the rect
     */
    int get_height() const
    {
        return m_height;
    }

    /**
     * @brief Copy constructor. Creates a new rectangle as a copy of an existing one.
     *
     * @param other The rectangle to copy.
     */
    rect(const rect& other) = default;

    /**
     * @brief Move constructor. Transfers ownership from another rectangle.
     *
     * @param other The rectangle to move.
     */
    rect(rect&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~rect() = default;

    /**
     * @brief Copy assignment operator.
     *
     * @param other The rectangle to copy.
     * @return Reference to the assigned rectangle.
     */
    rect& operator=(const rect& other) = default;

    /**
     * @brief Move assignment operator.
     *
     * @param other The rectangle to move.
     * @return Reference to the assigned rectangle.
     */
    rect& operator=(rect&& other) noexcept = default;

    /**
     * @brief Checks if a point lies within the boundaries of the rectangle (inclusive of borders).
     *
     * @param px The x-coordinate of the point to check.
     * @param py The y-coordinate of the point to check.
     * @return True if the point lies within or on the edges of the rectangle, otherwise false.
     */
    bool inside(int px, int py) const
    {
        return m_x <= px && px <= m_x + m_width && m_y <= py && py <= m_y + m_height;
    }

    /**
     * @brief Checks if a point lies strictly within the boundaries of the rectangle (excluding borders).
     *
     * @param px The x-coordinate of the point to check.
     * @param py The y-coordinate of the point to check.
     * @return True if the point lies strictly within the bounds of the rectangle, otherwise false.
     */
    bool inside_excluding_borders(int px, int py) const
    {
        return m_x <= px && px < m_x + m_width && m_y <= py && py < m_y + m_height;
    }

    /**
     * @brief Sets the size of the rectangle.
     *
     * @param new_width The new m_width of the rectangle.
     * @param new_height The new m_height of the rectangle.
     */
    void set_size(int new_width, int new_height)
    {
        m_width = new_width;
        m_height = new_height;
    }

    /**
     * @brief Resizes the rectangle by specified amounts.
     *
     * @param dw The amount to increase the m_width.
     * @param dh The amount to increase the m_height.
     */
    void resize(int dw, int dh)
    {
        m_width += dw;
        m_height += dh;
    }

    /**
     * @brief Returns the area of the rectangle.
     *
     * @return The area as an integer.
     */
    int area() const
    {
        return m_width * m_height;
    }

    /**
     * @brief Checks if the rectangle has valid dimensions (positive m_width and m_height).
     *
     * @return True if both m_width and m_height are positive, false otherwise.
     */
    bool is_valid() const
    {
        return m_width > 0 && m_height > 0;
    }

private:
    int m_width = -1;  /**< The width of the rectangle. Default is -1, indicating an uninitialized width. */
    int m_height = -1; /**< The height of the rectangle. Default is -1, indicating an uninitialized height. */
};

}

#endif // RECT_H
