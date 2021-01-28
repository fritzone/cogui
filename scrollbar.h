#ifndef SCROLLBAR_H
#define SCROLLBAR_H

namespace cogui
{

class control;

class scrollbar
{
public:
    enum class orientation
    {
        so_horizontal,
        so_vertical,
        so_both,
        so_none
    };

    scrollbar();

    static scrollbar vertical;
    static scrollbar horizontal;
    static scrollbar both;

    orientation get_orientation() const;
    void set_orientation(orientation o);

    void set_parent(control* c);
    control* get_parent() const;

    int get_handle_position() const;

private:

    scrollbar(orientation o);
    orientation m_orientation = orientation::so_none;
    control* m_parent = nullptr;
    int m_handle_position = 0;
};

}

#endif // SCROLLBAR_H
