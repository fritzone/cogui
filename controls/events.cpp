#include "events.h"
#include "curses.h"
#include "mouse.h"
#include "log.h"
#include "cogui.h"

cogui::events::keypress::keypress(cogui::events::key_class type, bool alt, bool shift, bool ctrl, const std::wstring &chardata) : m_type(type),
    m_alt(alt), m_shift(shift), m_ctrl(ctrl), m_chardata(chardata), m_key(chardata)
{
    static const std::wstring Ctrl = L"Ctrl-";
    static const std::wstring Alt = L"Alt-";
    static const std::wstring Shift = L"Shift-";

    // do not change the order
    if(m_shift)
    {
        std::size_t shift_pos =m_chardata.find(Shift);
        if(shift_pos == std::string::npos) m_chardata = Shift + m_chardata;
    }

    if(m_alt)
    {
        if(keymap.count(m_key) != 0)
        {
            m_type = keymap[m_key];
        }

        std::size_t alt_pos =m_chardata.find(Alt);
        if(alt_pos == std::string::npos) m_chardata = Alt + m_chardata;
    }

    if(m_ctrl)
    {
        if(keymap.count(m_key) != 0)
        {
            m_type = keymap[m_key];
        }
        std::size_t ctrl_pos =m_chardata.find(Ctrl);
        if(ctrl_pos == std::string::npos) m_chardata = Ctrl + m_chardata;
    }
}

bool cogui::events::keypress::handle()
{
    std::shared_ptr<cogui::events::keypress> copy = std::make_shared<cogui::events::keypress>(m_type, m_alt, m_shift, m_ctrl, m_chardata);
    return cogui::desktop::get().handle_key(copy);
}

std::wstring cogui::events::keypress::get_chardata()
{
    return m_chardata;
}

bool cogui::events::keypress::operator ==(const keypress &rhs) const
{
    bool first_check = (m_type == rhs.m_type && m_alt == rhs.m_alt && m_shift == rhs.m_shift && m_ctrl == rhs.m_ctrl && m_chardata == rhs.m_chardata);
    if(first_check) return true;
    if(m_hotkey)
    {
        log_debug() << cogui::utils::str2upper(m_chardata) << "==" <<cogui::utils::str2upper(rhs.m_chardata);

        return (m_alt == rhs.m_alt &&
                m_shift == rhs.m_shift && m_ctrl == rhs.m_ctrl &&
                cogui::utils::str2upper(m_chardata) == cogui::utils::str2upper(rhs.m_chardata));
    }
    return false;
}

bool cogui::events::keypress::operator ==(cogui::events::key_class r)
{
    log_debug() << "Comparing" << (int)m_type << "with" << (int)r;
    return this->m_type == r;
}

cogui::events::mouse_move::mouse_move(int x, int y) : mouse_event(x, y) {}

bool cogui::events::mouse_move::handle()
{
    return cogui::desktop::get().handle_mouse_move(get_x(),get_y());
}

cogui::events::mouse_event::mouse_event(int x, int y) : m_x(x), m_y(y)
{
}

int cogui::events::mouse_event::get_x() const
{
    return m_x;
}

int cogui::events::mouse_event::get_y() const
{
    return m_y;
}

cogui::events::mouse_right_up::mouse_right_up(int x, int y) : mouse_event(x, y)
{
}

bool cogui::events::mouse_right_up::handle()
{
    return cogui::desktop::get().handle_mouse_right_up(get_x(), get_y());
}

cogui::events::mouse_left_up::mouse_left_up(int x, int y) : mouse_event(x, y)
{
}

bool cogui::events::mouse_left_up::handle()
{
    return cogui::desktop::get().handle_mouse_left_up(get_x(), get_y());
}

cogui::events::mouse_left_click::mouse_left_click(int x, int y) : mouse_event(x, y)
{
}

bool cogui::events::mouse_left_click::handle()
{
    return cogui::desktop::get().handle_mouse_left_click(get_x(), get_y());
}

cogui::events::mouse_left_down::mouse_left_down(int x, int y) : mouse_event(x, y)
{
}

bool cogui::events::mouse_left_down::handle()
{
    return cogui::desktop::get().handle_mouse_left_down(get_x(), get_y());
}

cogui::events::mouse_right_down::mouse_right_down(int x, int y) : mouse_event(x, y)
{
}

bool cogui::events::mouse_right_down::handle()
{
    return cogui::desktop::get().handle_mouse_right_down(get_x(), get_y());
}

bool cogui::events::mouse_left_doubleclick::handle()
{
    return cogui::desktop::get().handle_mouse_doubleclick(get_x(), get_y());
}

bool cogui::events::is_function_key(key_class kc)
{
    switch(kc)
    {
    case key_class::key_f1: return true;
    case key_class::key_f2: return true;
    case key_class::key_f3: return true;
    case key_class::key_f4: return true;
    case key_class::key_f5: return true;
    case key_class::key_f6: return true;
    case key_class::key_f7: return true;
    case key_class::key_f8: return true;
    case key_class::key_f9: return true;
    case key_class::key_f10: return true;
    case key_class::key_f11: return true;
    case key_class::key_f12: return true;
    default: return false;
    }
}
