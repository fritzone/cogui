#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <miso.h>

#include "rect.h"

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

    // this signal is emitted when the handle of the scrollbar changes its position
    miso::signal<control*, int> sig_on_change {"on_scroll"};

    void set_dec_arrow_screen_position(const rect &dec_arrow_screen_position);
    void set_inc_arrow_screen_position(const rect &inc_arrow_screen_position);
    void set_handle_screen_position(const rect &handle_screen_position);

    // the position of scrollbar as drawn on the screen: arrows and handle
    rect m_dec_arrow_screen_position;
    rect m_inc_arrow_screen_position;
    rect m_handle_screen_position;

    void set_value(int v);
    int get_value() const;
    void step_up();
    void step_down();

private:

    scrollbar(orientation o);
    orientation m_orientation = orientation::so_none;
    control* m_parent = nullptr;
    int m_handle_position = 0;

    int m_max_value = 100;
    int m_min_value = 1;
    int m_current_value = 1;
    float m_step;

    bool m_dec_pos_set = false;
    bool m_inc_pos_set = false;

    void recalculate_step();
    void set_handle_position(int h);

    int m_dist;

    void debug_me();

};

}

#endif // SCROLLBAR_H
