#ifndef EVENTS_H
#define EVENTS_H

#include "utils.h"

#include <memory>
#include <map>

namespace cogui
{



namespace events
{


enum class event_type
{
    key_press,
    mouse_left_click,
    mouse_right_click,
    mouse_left_press,
    mouse_left_release,
    mouse_right_press,
    mouse_right_release,
    no_event,
    unknown
};


enum class key_class
{
    key_a,
    key_b,
    key_c,
    key_d,
    key_e,
    key_f,
    key_g,
    key_h,
    key_i,
    key_j,
    key_k,
    key_l,
    key_m,
    key_n,
    key_o,
    key_p,
    key_q,
    key_r,
    key_s,
    key_t,
    key_u,
    key_v,
    key_w,
    key_x,
    key_y,
    key_z,

    // the generic key for any character related key
    key_textinput,

    // if a key is a modifier, such as Alt, Ctrl, Shift
    key_modifier,

    // Escape
    key_escape,

    // The function keys
    key_f1,
    key_f2,
    key_f3,
    key_f4,
    key_f5,
    key_f6,
    key_f7,
    key_f8,
    key_f9,
    key_f10,
    key_f11,
    key_f12,

    // space modifier keys
    key_tab,
    key_space,
    key_backspace,
    key_return,

    // The big 6
    key_insert,
    key_delete,
    key_home,
    key_end,
    key_pgup,
    key_pgdn,

    // Arrows
    key_left,
    key_right,
    key_up,
    key_down,

    // keypad keys
    key_kp_div,
    key_kp_mul,
    key_kp_minus,
    key_kp_plus,
    key_kp_enter,
    key_kp_0,
    key_kp_1,
    key_kp_2,
    key_kp_3,
    key_kp_4,
    key_kp_5,
    key_kp_6,
    key_kp_7,
    key_kp_8,
    key_kp_9,

    // no key
    key_none
};

static std::map<std::wstring, key_class> keymap = {
    {L"a", key_class::key_a},
    {L"b", key_class::key_b},
    {L"c", key_class::key_c},
    {L"d", key_class::key_d},
    {L"e", key_class::key_e},
    {L"f", key_class::key_f},
    {L"g", key_class::key_g},
    {L"h", key_class::key_h},
    {L"i", key_class::key_i},
    {L"j", key_class::key_j},
    {L"k", key_class::key_k},
    {L"l", key_class::key_l},
    {L"m", key_class::key_m},
    {L"n", key_class::key_n},
    {L"o", key_class::key_o},
    {L"p", key_class::key_p},
    {L"q", key_class::key_q},
    {L"r", key_class::key_r},
    {L"s", key_class::key_s},
    {L"t", key_class::key_t},
    {L"u", key_class::key_u},
    {L"v", key_class::key_v},
    {L"w", key_class::key_w},
    {L"x", key_class::key_x},
    {L"y", key_class::key_y},
    {L"z", key_class::key_z},
};

/**
 * @brief The event class the pure abstract of representing an event (keyboard / mouse) that nees to
 * be handled by the framework
 */
class event
{
public:

    template<class T, class... Args>
    static std::shared_ptr<T> create(Args... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    virtual bool handle() = 0;
};

class mouse_event : public event
{
public:
    mouse_event(int x, int y);
    virtual bool handle() = 0;

    int x() const;
    int y() const;

private:

    int m_x;
    int m_y;

};

class mouse_move : public mouse_event
{
public:
    mouse_move(int x, int y);
    bool handle() override;
};

class mouse_right_up : public mouse_event
{
public:
    mouse_right_up(int x, int y);
    bool handle() override;
};


class mouse_left_up : public mouse_event
{
public:
    mouse_left_up(int x, int y);
    bool handle() override;
};

class mouse_left_down : public mouse_event
{
public:
    mouse_left_down(int x, int y);
    bool handle() override;
};

class mouse_right_down : public mouse_event
{
public:
    mouse_right_down(int x, int y);
    bool handle() override;
};

class mouse_left_click : public mouse_event
{
public:
    mouse_left_click(int x, int y);
    bool handle() override;
};


class keypress : public event, public std::enable_shared_from_this<keypress>
{
public:
    keypress() = default;
    keypress(key_class type, bool alt, bool shift, bool ctrl, const std::wstring& chardata);
    bool handle() override;
    std::wstring get_chardata();
    bool operator == (const keypress& rhs) const
    {
        bool first_check = (m_type == rhs.m_type && m_alt == rhs.m_alt && m_shift == rhs.m_shift && m_ctrl == rhs.m_ctrl && m_chardata == rhs.m_chardata);
        if(first_check) return true;
        if(m_hotkey)
        {
            return (m_type == rhs.m_type && m_alt == rhs.m_alt &&
                    m_shift == rhs.m_shift && m_ctrl == rhs.m_ctrl &&
                    cogui::utils::str2upper(m_chardata) == cogui::utils::str2upper(rhs.m_chardata));
        }
        return false;
    }

    bool operator == (key_class r);

    std::shared_ptr<keypress> getptr()
    {
        return shared_from_this();
    }

    void set_as_hotkey()
    {
        m_hotkey = true;
    }

    bool is_hotkey()
    {
        return m_hotkey;
    }

    key_class get_type() const
    {
        return m_type;
    }

    void set_type(key_class nt)
    {
        m_type = nt;
    }

    void set_alt_modifier(bool b)
    {
        m_alt = b;
    }
    void set_ctrl_modifier(bool b)
    {
        m_ctrl = b;
    }
    void set_shift_modifier(bool b)
    {
        m_shift = b;
    }

    bool get_alt() const { return m_alt; }
    bool get_ctrl() const { return m_ctrl; }
    bool get_shift() const { return m_shift; }

    void set_chardata(const std::wstring chardata)
    {
        m_chardata = chardata;
    }

    std::wstring get_chardata() const
    {
        return m_chardata;
    }

private:
    key_class m_type = key_class::key_none;
    bool m_alt = false;
    bool m_shift = false;
    bool m_ctrl = false;
    std::wstring m_chardata = L"";
    bool m_hotkey = false;
    std::wstring m_key = L"";
};

}
}

#endif // EVENTS_H
