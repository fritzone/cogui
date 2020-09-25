#ifndef EVENTS_H
#define EVENTS_H

#include <memory>
#include "utils.h"

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
    key_textinput,
    key_escape,
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
    key_tab,
    key_insert,
    key_delete,
    key_home,
    key_end,
    key_pgup,
    key_pgdn,
    key_left,
    key_right,
    key_up,
    key_down,
    key_backspace,
    key_return,
    key_kp_div,
    key_kp_mul,
    key_kp_minus,
    key_kp_plus,
    key_kp_enter
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


class key : public event, public std::enable_shared_from_this<key>
{
public:
    key(key_class type, bool alt, bool shift, bool ctrl, const std::wstring& chardata);
    bool handle() override;
    std::wstring get_chardata();
    bool operator == (const key& rhs) const
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
    std::shared_ptr<key> getptr()
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

private:
    key_class m_type;
    bool m_alt;
    bool m_shift;
    bool m_ctrl;
    std::wstring m_chardata;
    bool m_hotkey = false;
};

}
}

#endif // EVENTS_H
