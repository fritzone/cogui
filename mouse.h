#ifndef MOUSE_H
#define MOUSE_H


class mouse
{
public:

    enum class button
    {
        left,
        right,
        left_and_right,
        none
    };

    static mouse& get();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    button buttons() const;
    void set_button(button b);
    void clear_button(button b);

private:
    mouse();

    int m_x;
    int m_y;
    button m_button = button::none;
};

#endif // MOUSE_H
