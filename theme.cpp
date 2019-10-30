#include "theme.h"
#include "desktop.h"
#include "graphics.h"
#include "window.h"
#include "control.h"
#include "button.h"

#include "loguru.h"

namespace cogui
{

template <class T>
T repeat(T str, const std::size_t n)
{
    if (n == 0) {
    str.clear();
    str.shrink_to_fit();
    return str;
    }

    if (n == 1 || str.empty()) return str;

    const auto period = str.size();

    if (period == 1) {
    str.append(n - 1, str.front());
    return str;
    }

    str.reserve(period * n);

    std::size_t m {2};

    for (; m < n; m *= 2) str += str;

    str.append(str.c_str(), (n - (m / 2)) * period);

    return str;
}

template <typename S, typename T, typename = std::enable_if<std::is_integral<T>::value> >
S operator*(S str, const T n)
{
    return repeat(std::move(str), static_cast<std::size_t>(n));
}

std::wstring line(int l, std::wstring chr)
{
    return chr * l;
}

template<typename T, typename S>
void draw(T x, T y, S s)
{
    desktop::get().set_chars(x, y, s);
    desktop::get().getGraphics()->draw(x, y, s.c_str());
}

template<>
void draw<int,const wchar_t*>(int x, int y, const wchar_t* s)
{
    desktop::get().set_chars(x, y, s);
    desktop::get().getGraphics()->draw(x, y, s);
}
} // namespace

void cogui::theme::clear(const control &c)
{
    int top = c.getY();
    for(int y = top; y <= top + c.getHeight(); y++)
    {
        cogui::draw(c.getX(), y, cogui::line(c.getWidth() + 2, L" "));
    }
}

void cogui::theme::draw_window(const cogui::window &w)
{
    bool rs = w.getDrawState() == window::draw_state::normal;

    auto line_char = rs ? WND_HORZ_LINE : HORZ_LINE_RESIZE;
    auto vert_line_char = rs ? WND_VERT_LINE : VERT_LINE_RESIZE;
    auto ul_corner_char = rs ? WND_UL_CORNER : UL_CORNER_RESIZE;
    auto ur_corner_char = rs ? WND_UR_CORNER : UR_CORNER_RESIZE;
    auto ll_corner_char = rs ? WND_LL_CORNER : LL_CORNER_RESIZE;
    auto lr_corner_char = rs ? WND_LR_CORNER : LR_CORNER_RESIZE;
    auto sysmenu_char = rs ? WND_SYSMENU : WND_SYSMENU_RESIZE;
    auto title_delim_left_char = rs ? WND_TITLE_DELIM_LEFT : WND_TITLE_DELIM_LEFT_RESIZE;
    auto title_delim_right_char = rs ? WND_TITLE_DELIM_RIGHT : WND_TITLE_DELIM_RIGHT_RESIZE;
    auto close_char = rs ? WND_CLOSE : WND_CLOSE_RESIZE;
    auto maximize_char = rs ? WND_MAXIMIZE : WND_MAXIMIZE_RESIZE;

    // top line
    cogui::draw(w.getX(), w.getY(), ul_corner_char + cogui::line(w.getWidth(), line_char) + ur_corner_char);
    // bottom line
    cogui::draw(w.getX(), w.getY() + w.getHeight(), ll_corner_char + cogui::line(w.getWidth(), line_char) +
        (w.resizeable() ? WND_LR_RESIZE : lr_corner_char) );

    // side lines
    for(int i=1; i< w.getHeight(); i++)
    {
        cogui::draw(w.getX(), w.getY() + i, vert_line_char);
        cogui::draw(w.getX() + w.getWidth() + 1, w.getY() + i, vert_line_char);
    }

    int available_width = w.getWidth(); // -3 because of the begin and end chars for title separator
    // buttons
    if(w.hasCloseButton())
    {
        available_width -= close_char.length();
        //info() << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.getX() + available_width, w.getY(), close_char);

        w.update_close_btn_pos(w.getX() + available_width + 1);
    }
    if(w.hasMaximizeButton())
    {
        available_width -= maximize_char.length() - 1;
        // info() << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.getX() + available_width , w.getY(), maximize_char);
        if(w.hasCloseButton()) // remove ugly close and end buttons from window titlebar
        {
            int newx = w.getX() + available_width + maximize_char.length() - 1;
            cogui::draw(newx, w.getY(), L" ");
        }
    }

    // if there is a system menu
    if(w.hasSysmenuButton())
    {
        available_width -= sysmenu_char.length();
        cogui::draw(w.getX() + 1, w.getY(), sysmenu_char);
    }

    // title
    if(!w.getTitle().empty())
    {
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = w.getX() + available_width / 2 - w.getTitle().length() / 2;
        int right = w.getX() + available_width / 2 + w.getTitle().length() / 2 + title_delim_left_char.length() + w.getTitle().length() % 2;
        cogui::draw(lefts, w.getY(), title_delim_left_char);
        int title_left = lefts + title_delim_left_char.length();
        cogui::draw(title_left, w.getY(), w.getTitle());
        cogui::draw(right, w.getY(), title_delim_right_char);
    }
}

void cogui::theme::draw_button(const cogui::button &b)
{
    auto ul_char = BTN_UL_CORNER_STATE_UP ;
    auto ll_char = BTN_LL_CORNER_STATE_UP ;
    auto ur_char = BTN_UR_CORNER_STATE_UP ;
    auto lr_char = BTN_LR_CORNER_STATE_UP ;
    auto top_char = BTN_TOP_BORDER_UP ;
    auto bottom_char = BTN_BOTTOM_BORDER_UP ;
    auto left_border = BTN_LEFT_UP ;
    auto right_border = BTN_RIGHT_UP ;

    if(b.getFocusState() == cogui::control::focus_state::focused)
    {
        ul_char = BTN_UL_CORNER_STATE_FOCUSED;
        ll_char = BTN_LL_CORNER_STATE_FOCUSED;
        ur_char = BTN_UR_CORNER_STATE_FOCUSED;
        lr_char = BTN_LR_CORNER_STATE_FOCUSED;
        top_char = BTN_TOP_BORDER_FOCUSED;
        bottom_char = BTN_BOTTOM_BORDER_FOCUSED;
        left_border = BTN_LEFT_FOCUSED;
        right_border = BTN_RIGHT_FOCUSED;
    }

    if(b.state() == control::press_state::pressed)
    {
        ul_char = BTN_UL_CORNER_STATE_PRESSED;
        ll_char = BTN_LL_CORNER_STATE_PRESSED;
        ur_char = BTN_UR_CORNER_STATE_PRESSED;
        lr_char = BTN_LR_CORNER_STATE_PRESSED;
        top_char = BTN_TOP_BORDER_PRESSED;
        bottom_char = BTN_BOTTOM_BORDER_PRESSED;
        left_border = BTN_LEFT_PRESSED;
        right_border = BTN_RIGHT_PRESSED;
    }

    // upper left corner
    cogui::draw(b.getX(), b.getY(), ul_char);
    cogui::draw(b.getX(), b.getY() + b.getHeight(), ll_char);
    cogui::draw(b.getX() + b.getWidth(), b.getY(), ur_char);
    cogui::draw(b.getX() + b.getWidth(), b.getY() + b.getHeight(), lr_char);

    // top border of button
    cogui::draw(b.getX() + 1, b.getY(), cogui::line(b.getWidth() - 1, top_char ) );
    cogui::draw(b.getX() + 1, b.getY() + b.getHeight(), cogui::line(b.getWidth() - 1, bottom_char) );

    // side lines
    for(int i=1; i< b.getHeight(); i++)
    {
        cogui::draw(b.getX(), b.getY() + i, left_border);
        cogui::draw(b.getX() + b.getWidth(), b.getY() + i, right_border);
    }

    // button text
    cogui::draw((int)(b.getX() + b.getWidth() / 2 - b.getTitle().length() / 2), b.getY() + b.getHeight() / 2, b.getTitle());


}
