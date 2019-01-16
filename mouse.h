#ifndef MOUSE_H
#define MOUSE_H


class mouse
{
public:

    enum class state
    {
	left_down,
	right_down,
	left_and_right_down
    };

    static mouse& get();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

private:

    int m_x;
    int m_y;

    mouse();
};

#endif // MOUSE_H
