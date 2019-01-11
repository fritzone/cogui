#ifndef CONTROL_H
#define CONTROL_H

namespace cogui
{

class control
{
public:
    control(int x, int y, int width, int height);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

private:

    int m_x;
    int m_y;
    int m_w;
    int m_h;
};

}

#endif // CONTROL_H
