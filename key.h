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
    abstract_hotkey_handler(H h) : m_hh(new hotkey_handler(h)) {}
    virtual bool handle() {return m_hh->handle();}
    std::shared_ptr<hh_base> m_hh;
    cogui::key* k = nullptr;
    void set_window(cogui::window *win)
    {
        m_hh->set_window(win);
    }
};



class key
{
public:

    // Standard letter keys
    static cogui::key A;
    static cogui::key B;
    static cogui::key C;
    static cogui::key D;
    static cogui::key E;
    static cogui::key F;
    static cogui::key G;
    static cogui::key H;
    static cogui::key I;
    static cogui::key J;
    static cogui::key K;
    static cogui::key L;
    static cogui::key M;
    static cogui::key N;
    static cogui::key O;
    static cogui::key P;
    static cogui::key Q;
    static cogui::key R;
    static cogui::key S;
    static cogui::key T;
    static cogui::key U;
    static cogui::key V;
    static cogui::key W;
    static cogui::key X;
    static cogui::key Y;
    static cogui::key Z;

    // Numbers
    static cogui::key Number_1;
    static cogui::key Number_2;
    static cogui::key Number_3;
    static cogui::key Number_4;
    static cogui::key Number_5;
    static cogui::key Number_6;
    static cogui::key Number_7;
    static cogui::key Number_8;
    static cogui::key Number_9;
    static cogui::key Number_0;

    // punctuation keys
    static cogui::key Comma;                        // The , key
    static cogui::key FullStop;                     // The . key
    static cogui::key Slash;                        // The / key
    static cogui::key Semicolon;                    // The ; key
    static cogui::key Apostrophe;                   // The ' key
    static cogui::key OpeningSquareBracket;         // The [ key
    static cogui::key ClosingSquareBracket;         // The ] key
    static cogui::key Backslash;                    // The \ key
    static cogui::key Equal;                        // The = key
    static cogui::key Minus;                        // The - key
    static cogui::key Grave;                        // the ` key

    // function keys
    static cogui::key F1;
    static cogui::key F2;
    static cogui::key F3;
    static cogui::key F4;
    static cogui::key F5;
    static cogui::key F6;
    static cogui::key F7;
    static cogui::key F8;
    static cogui::key F9;
    static cogui::key F10;
    static cogui::key F11;
    static cogui::key F12;

    // Escape
    static cogui::key Escape;

    // Arrow keys
    static cogui::key Up;
    static cogui::key Down;
    static cogui::key Left;
    static cogui::key Right;

    // Jumping keys
    static cogui::key Home;
    static cogui::key End;
    static cogui::key PgUp;
    static cogui::key PgDn;

    // typing keys
    static cogui::key Insert;
    static cogui::key Delete;
    static cogui::key Space;
    static cogui::key Enter;

    // modifier keys
    static cogui::key Alt;
    static cogui::key Ctrl;
    static cogui::key Shift;

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
        ahh->k = this;
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
    
template <const cogui::key* K> struct on
{
    static cogui::key& press;
};


/*
class window;

#include <functional>

    template<class KeyCode> 
    using OnKey = fluent::NamedType<std::function<void(window*, KeyCode)>, struct OnKeyHelper<KeyCode>::key>;
    
    template<class KeyCode> struct OnKeyHelper
    {
        using key = KeyCode;
    };

    
    template<> struct on_key<cogui::key::A> {  };
*/    
}

#endif // KEY_H
