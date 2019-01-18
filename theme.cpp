#include "theme.h"
#include "desktop.h"
#include "graphics.h"
#include "window.h"
#include "control.h"

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
    desktop::get().graphics()->draw(x, y, s.c_str());
}

template<>
void draw<int,const wchar_t*>(int x, int y, const wchar_t* s)
{
    desktop::get().set_chars(x, y, s);
    desktop::get().graphics()->draw(x, y, s);
}
}

void cogui::theme::clear(const control &c)
{
    int top = c.y();
    for(int y = top; y <= top + c.height(); y++)
    {
        cogui::draw(c.x(), y, cogui::line(c.width() + 2, L" "));
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
    cogui::draw(w.x(), w.y(), ul_corner_char + cogui::line(w.width(), line_char) + ur_corner_char);
    // bottom line
    cogui::draw(w.x(), w.y() + w.height(), ll_corner_char + cogui::line(w.width(), line_char) +
        (w.resizeable() ? WND_LR_RESIZE : lr_corner_char) );

    // side lines
    for(int i=1; i< w.height(); i++)
    {
        cogui::draw(w.x(), w.y() + i, vert_line_char);
        cogui::draw(w.x() + w.width() + 1, w.y() + i, vert_line_char);
    }

    int available_width = w.width(); // -3 because of the begin and end chars for title separator
    // buttons
    if(w.hasCloseButton())
    {
        available_width -= close_char.length();
        LOG_S(INFO) << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.x() + available_width, w.y(), close_char);
    }
    if(w.hasMaximizeButton())
    {
        available_width -= maximize_char.length() - 1;
        LOG_S(INFO) << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.x() + available_width , w.y(), maximize_char);
        if(w.hasCloseButton()) // remove ugly close and end buttons from window titlebar
        {
            int newx = w.x() + available_width + maximize_char.length() - 1;
            cogui::draw(newx, w.y(), L" ");
        }
    }

    // if there is a system menu
    if(w.hasSysmenuButton())
    {
        available_width -= sysmenu_char.length();
        cogui::draw(w.x() + 1, w.y(), sysmenu_char);
    }

    // title
    if(!w.title().empty())
    {
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = w.x() + available_width / 2 - w.title().length() / 2;
        int right = w.x() + available_width / 2 + w.title().length() / 2 + title_delim_left_char.length() + w.title().length() % 2;
        cogui::draw(lefts, w.y(), title_delim_left_char);
        int title_left = lefts + title_delim_left_char.length();
        cogui::draw(title_left, w.y(), w.title());
        cogui::draw(right, w.y(), title_delim_right_char);
    }

    cogui::desktop::get().graphics()->refresh_screen();

}
