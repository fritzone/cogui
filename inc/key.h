#ifndef KEY_H
#define KEY_H

#include "events.h"

#include <map>
#include <initializer_list>
#include <vector>

namespace cogui {

class window;
class key;

struct hh_base
{
    hh_base() = default;
    virtual bool handle() = 0;
    virtual void set_window(window*) = 0;
};

template<typename H> struct hotkey_handler : public hh_base
{
    hotkey_handler(H h) : m_handler(h) {}

    virtual bool handle() override
    {
        m_handler(m_window);
        return true;
    }

    virtual void set_window(cogui::window *win) override
    {
        m_window = win;
    }

    H m_handler;
    cogui::window* m_window = nullptr;

};

struct abstract_hotkey_handler
{
    template<class H>
    abstract_hotkey_handler(H h) : m_hh(new hotkey_handler(h))
    {}

    void set_window(cogui::window *win)
    {
        m_hh->set_window(win);
    }

    virtual bool handle()
    {
        return m_hh->handle();
    }


public:
    cogui::key *get_key() const;

    void set_key(cogui::key *newK);

private:

    std::shared_ptr<hh_base> m_hh;
    cogui::key* k = nullptr;

    };



class key
{
public:

    // used to create hotkeys
    key operator + (const key& other);

    key(const events::keypress& generator);
    key() = default;

    std::wstring get_character() const
    {
        return m_generator.get_chardata();
    }
    
    template<class H> std::shared_ptr<abstract_hotkey_handler> operator = (H h)
    {
        std::shared_ptr<abstract_hotkey_handler> ahh = std::make_shared<abstract_hotkey_handler>(h);
        ahh->set_key(this);
        return ahh;
    }

    events::keypress& generator()
    {
        return m_generator;
    }

private:
    events::keypress m_generator;
};

using hotkey_associations = std::vector<std::shared_ptr<abstract_hotkey_handler>>;

template <typename T> struct on_impl
{
    static cogui::key& press;
};

#define on(KEY) on_impl<KEY>::press

#define DEFINE_KEY_CLASS(name, key_type, alt, shift, ctrl) \
struct name { \
        static auto constexpr ptr##name = []()->cogui::key& { \
            cogui::key* k = new cogui::key{ {cogui::events::key_class::key_##key_type, alt, shift, ctrl, L ## #key_type } }; \
            return *k; \
    }; \
};

// Macro definitions for all modifier combinations for each key
#define DEFINE_KEY_COMBINATIONS(key_name) \
DEFINE_KEY_CLASS(NoMod_##key_name, key_name, false, false, false) \
    DEFINE_KEY_CLASS(Shift_##key_name, key_name, false, true, false) \
    DEFINE_KEY_CLASS(Ctrl_##key_name, key_name, false, false, true) \
    DEFINE_KEY_CLASS(Alt_##key_name, key_name, true, false, false) \
    DEFINE_KEY_CLASS(Ctrl_Alt_##key_name, key_name, true, false, true) \
    DEFINE_KEY_CLASS(Ctrl_Shift_##key_name, key_name, false, true, true) \
    DEFINE_KEY_CLASS(Alt_Shift_##key_name, key_name, true, true, false) \
    DEFINE_KEY_CLASS(Ctrl_Alt_Shift_##key_name, key_name, true, true, true)

    // Define key combinations for all keys in the enum
    DEFINE_KEY_COMBINATIONS(a)
    DEFINE_KEY_COMBINATIONS(b)
    DEFINE_KEY_COMBINATIONS(c)
    DEFINE_KEY_COMBINATIONS(d)
    DEFINE_KEY_COMBINATIONS(e)
    DEFINE_KEY_COMBINATIONS(f)
    DEFINE_KEY_COMBINATIONS(g)
    DEFINE_KEY_COMBINATIONS(h)
    DEFINE_KEY_COMBINATIONS(i)
    DEFINE_KEY_COMBINATIONS(j)
    DEFINE_KEY_COMBINATIONS(k)
    DEFINE_KEY_COMBINATIONS(l)
    DEFINE_KEY_COMBINATIONS(m)
    DEFINE_KEY_COMBINATIONS(n)
    DEFINE_KEY_COMBINATIONS(o)
    DEFINE_KEY_COMBINATIONS(p)
    DEFINE_KEY_COMBINATIONS(q)
    DEFINE_KEY_COMBINATIONS(r)
    DEFINE_KEY_COMBINATIONS(s)
    DEFINE_KEY_COMBINATIONS(t)
    DEFINE_KEY_COMBINATIONS(u)
    DEFINE_KEY_COMBINATIONS(v)
    DEFINE_KEY_COMBINATIONS(w)
    DEFINE_KEY_COMBINATIONS(x)
    DEFINE_KEY_COMBINATIONS(y)
    DEFINE_KEY_COMBINATIONS(z)

    DEFINE_KEY_COMBINATIONS(textinput)
    DEFINE_KEY_COMBINATIONS(modifier)
    DEFINE_KEY_COMBINATIONS(escape)
    DEFINE_KEY_COMBINATIONS(f1)
    DEFINE_KEY_COMBINATIONS(f2)
    DEFINE_KEY_COMBINATIONS(f3)
    DEFINE_KEY_COMBINATIONS(f4)
    DEFINE_KEY_COMBINATIONS(f5)
    DEFINE_KEY_COMBINATIONS(f6)
    DEFINE_KEY_COMBINATIONS(f7)
    DEFINE_KEY_COMBINATIONS(f8)
    DEFINE_KEY_COMBINATIONS(f9)
    DEFINE_KEY_COMBINATIONS(f10)
    DEFINE_KEY_COMBINATIONS(f11)
    DEFINE_KEY_COMBINATIONS(f12)

    DEFINE_KEY_COMBINATIONS(tab)
    DEFINE_KEY_COMBINATIONS(space)
    DEFINE_KEY_COMBINATIONS(backspace)
    DEFINE_KEY_COMBINATIONS(return)
    DEFINE_KEY_COMBINATIONS(insert)
    DEFINE_KEY_COMBINATIONS(delete)
    DEFINE_KEY_COMBINATIONS(home)
    DEFINE_KEY_COMBINATIONS(end)
    DEFINE_KEY_COMBINATIONS(pgup)
    DEFINE_KEY_COMBINATIONS(pgdn)

    DEFINE_KEY_COMBINATIONS(left)
    DEFINE_KEY_COMBINATIONS(right)
    DEFINE_KEY_COMBINATIONS(up)
    DEFINE_KEY_COMBINATIONS(down)

    DEFINE_KEY_COMBINATIONS(kp_div)
    DEFINE_KEY_COMBINATIONS(kp_mul)
    DEFINE_KEY_COMBINATIONS(kp_minus)
    DEFINE_KEY_COMBINATIONS(kp_plus)
    DEFINE_KEY_COMBINATIONS(kp_enter)
    DEFINE_KEY_COMBINATIONS(kp_comma)
    DEFINE_KEY_COMBINATIONS(kp_0)
    DEFINE_KEY_COMBINATIONS(kp_1)
    DEFINE_KEY_COMBINATIONS(kp_2)
    DEFINE_KEY_COMBINATIONS(kp_3)
    DEFINE_KEY_COMBINATIONS(kp_4)
    DEFINE_KEY_COMBINATIONS(kp_5)
    DEFINE_KEY_COMBINATIONS(kp_6)
    DEFINE_KEY_COMBINATIONS(kp_7)
    DEFINE_KEY_COMBINATIONS(kp_8)
    DEFINE_KEY_COMBINATIONS(kp_9)

    DEFINE_KEY_COMBINATIONS(1)
    DEFINE_KEY_COMBINATIONS(2)
    DEFINE_KEY_COMBINATIONS(3)
    DEFINE_KEY_COMBINATIONS(4)
    DEFINE_KEY_COMBINATIONS(5)
    DEFINE_KEY_COMBINATIONS(6)
    DEFINE_KEY_COMBINATIONS(7)
    DEFINE_KEY_COMBINATIONS(8)
    DEFINE_KEY_COMBINATIONS(9)
    DEFINE_KEY_COMBINATIONS(0)

    DEFINE_KEY_COMBINATIONS(none)

#undef DEFINE_KEY_CLASS
#undef DEFINE_KEY_COMBINATIONS

}

#endif // KEY_H
