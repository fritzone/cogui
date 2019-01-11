#include "theme.h"
#include "desktop.h"
#include "graphics.h"
#include "window.h"

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

std::wstring line(int l, theme t)
{
    return t.HORZ_LINE * l;
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

void cogui::theme::draw_window(const cogui::window &w)
{
    // top line
    cogui::draw(w.x(), w.y(), UL_CORNER + cogui::line(w.width(), *this) + UR_CORNER );
    // bottom line
    cogui::draw(w.x(), w.y() + w.height(), LL_CORNER + cogui::line(w.width(), *this) +
        (w.resizeable() ? LR_RESIZE : LR_CORNER) );

    // side lines
    for(int i=1; i< w.height(); i++)
    {
        cogui::draw(w.x(), w.y() + i, VERT_LINE);
        cogui::draw(w.x() + w.width() + 1, w.y() + i, VERT_LINE);
    }

    int available_width = w.width(); // -3 because of the begin and end chars for title separator
    // buttons
    if(w.hasCloseButton())
    {
        available_width -= WND_CLOSE.length();
        LOG_S(INFO) << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.x() + available_width, w.y(), WND_CLOSE);
    }
    if(w.hasMaximizeButton())
    {
        available_width -= WND_MAXIMIZE.length() - 1;
        LOG_S(INFO) << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.x() + available_width , w.y(), WND_MAXIMIZE);
        if(w.hasCloseButton()) // remove ugly close and end buttons from window titlebar
        {
            int newx = w.x() + available_width + WND_MAXIMIZE.length() - 1;
            cogui::draw(newx, w.y(), L" ");
        }
    }

    // if there is a system menu
    if(w.hasSysmenuButton())
    {
        available_width -= WND_SYSMENU.length();
        cogui::draw(w.x() + 1, w.y(), WND_SYSMENU);
    }

    // title
    if(!w.title().empty())
    {
        available_width -= WND_TITLE_DELIM_LEFT.length() + WND_TITLE_DELIM_RIGHT.length(); // two title delimiters
        int lefts = w.x() + available_width / 2 - w.title().length() / 2;
        int right = w.x() + available_width / 2 + w.title().length() / 2 + WND_TITLE_DELIM_LEFT.length();
        cogui::draw(lefts, w.y(), WND_TITLE_DELIM_LEFT);
        cogui::draw(right, w.y(), WND_TITLE_DELIM_RIGHT);
        int title_left = lefts + WND_TITLE_DELIM_LEFT.length();
        cogui::draw(title_left, w.y(), w.title());
    }

    cogui::desktop::get().graphics()->refresh_screen();

}
