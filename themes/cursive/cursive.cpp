#include "cursive.h"
#include "desktop.h"
#include "graphics.h"
#include "window.h"
#include "control.h"
#include "button.h"
#include "checkbox.h"

#include "log.h"

#include <variant>
#include <algorithm>

extern "C" cogui::theme* create()
{
    return static_cast<cogui::theme*>(new cogui::themes::cursive);
}

void cogui::themes::cursive::clear(const cogui::control &c)
{
    int top = c.getY();
    int h = c.getHeight();
    int x = c.getX();
    int w = c.getWidth();
    for(int y = top; y <= top + h; y++)
    {
        cogui::draw(x, y, cogui::line(w + 2, L" "));
    }
}

void cogui::themes::cursive::draw_window(const cogui::window &w)
{
    if(!w.isVisible())
    {
        return;
    }

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

    int close_pos = -1;
    int sysmenu_pos = -1;
    int maximize_pos = -1;

    if(w.hasCloseButton())
    {
        available_width -= close_char.length();
        //log_info() << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.getX() + available_width, w.getY(), close_char);
        close_pos = w.getX() + available_width + 1;

    }
    if(w.hasMaximizeButton())
    {
        available_width -= maximize_char.length() - 1;
        // log_info() << "wdth:" << w.width() << " avail:" << available_width;

        cogui::draw(w.getX() + available_width , w.getY(), maximize_char);
        maximize_pos = w.getX() + available_width + 1;
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
        cogui::draw(w.getX() + 1, w.getY(), w.getSystemMenu().isOpened() ? WND_SYSMENU_DOWN : sysmenu_char);
        sysmenu_pos = w.getX() + 1 + 1 ;
    }

    // title
    if(!w.getTitle().empty())
    {
        std::wstring wtitle = w.getTitle();
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = w.getX() + available_width / 2 - (wtitle.length() +1) / 2;

        std::wstring t = title_delim_left_char + wtitle + title_delim_right_char;

        cogui::draw(lefts, w.getY(), t);
    }

    w.update_titlebar_btn_positions(close_pos, sysmenu_pos, maximize_pos);

}

void cogui::themes::cursive::draw_button(const cogui::button &b)
{
    if(!b.isVisible())
    {
        return;
    }

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
    int title_x = (int)(b.getX() + b.getWidth() / 2 - b.getTitle().length() / 2);
    std::wstring title_to_draw = b.getTitle();
    if(title_x <= b.getX())
    {
        title_x = b.getX() + 1;
    }

    if(title_to_draw.length() >= b.getWidth())
    {
        title_to_draw = title_to_draw.substr(0, b.getWidth() - 4) + L"...";
    }

    if(b.getHeight() >= 2)
    {
        int title_y = b.getY() + b.getHeight() / 2;
        cogui::draw(b.getX() + 1, title_y, cogui::line(b.getWidth() - 2, L" "));
        if(b.getFocusState() == cogui::control::focus_state::focused)
        {
            // log_info()<<"focused, drawing underlined";
            cogui::draw_title(title_x, title_y, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
        }
        else
        {
            cogui::draw_title(title_x, title_y, title_to_draw);
        }
    }
}

void cogui::themes::cursive::draw_menu(const cogui::menu &m)
{
    int top = m.getY();
    int h = m.getHeight();
    int x = m.getX();
    int wi = m.getWidth();
    for(int y = top; y <= top + h; y++)
    {
        cogui::draw(x, y, cogui::line(wi + 2, L" "));
    }

    cogui::draw(m.getX(), m.getY(), MNU_UL_CORNER);
    cogui::draw(m.getX(), m.getY() + m.getHeight(), MNU_LL_CORNER);
    cogui::draw(m.getX() + m.getWidth(), m.getY(), MNU_UR_CORNER);
    cogui::draw(m.getX() + m.getWidth(), m.getY() + m.getHeight(), MNU_LR_CORNER);

    cogui::draw(m.getX() + 1, m.getY(), cogui::line(m.getWidth() - 1, MNU_HORIZONTAL));
    cogui::draw(m.getX() + 1, m.getY() + m.getHeight(), cogui::line(m.getWidth() - 1, MNU_HORIZONTAL));

    if(m.isSysmenu())
    {
        cogui::draw(m.getX(), m.getY(), MNU_SYSMENU_TOP);
    }

    int mc = 0;
    for(int y = top+1; y < top + h; y++)
    {
        cogui::draw(x, y, MNU_VERTICAL);
        cogui::draw(x + wi, y, MNU_VERTICAL);
        // log_info() << "LASTSEL:" << m.getLastSelectedIndex() << " mc=" << mc;

        std::wstring titleToDraw = m[mc].getTitle();
        while(titleToDraw.length() < m.getWidth() - 1) titleToDraw += L" ";

        if(mc == m.getLastSelectedIndex())
        {
            desktop::get().getGraphics()->setColors(graphics::color::black, graphics::color::white);
            cogui::draw_title(x + 1, y, titleToDraw);
            desktop::get().getGraphics()->setColors(graphics::color::white, graphics::color::black);
        }
        else
        {
            cogui::draw_title(x + 1, y, titleToDraw);
        }

        mc ++;
    }
}

void cogui::themes::cursive::draw_checkbox(const checkbox &c)
{
    if(!c.isVisible())
    {
        return;
    }

    int title_x = (int)(c.getX() + c.getWidth() / 2 - c.getTitle().length() / 2);

    if(title_x <= c.getX() + 2)
    {
        title_x = c.getX() + 4;
    }

    std::wstring title_to_draw = c.getTitle();

    if(static_cast<int>(title_to_draw.length()) >= c.getWidth() - 4)
    {
        title_to_draw = title_to_draw.substr(0, c.getWidth() - 4 - 4) + L"...";
    }

    int drawY = c.getY() + c.getHeight() / 2;

    if(c.getFocusState() == cogui::control::focus_state::focused)
    {
        cogui::draw(c.getX(), drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::underline & cogui::textflags::bold);
        cogui::draw_title(title_x, drawY, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
    }
    else
    {
        cogui::draw(c.getX(), drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::normal);
        cogui::draw_title(title_x, drawY, title_to_draw);
    }
}

int cogui::themes::cursive::minimum_checkbox_width(const cogui::checkbox &c)
{
    return c.getTitle().length() + 2; // +2 for the checkmarek followed by a space
}

int cogui::themes::cursive::minimum_checkbox_height(const cogui::checkbox &c)
{
    return 1;
}

int cogui::themes::cursive::minimum_button_width(const cogui::button &b)
{
    return b.getTitle().length() + 2; // +2 for the beginning and ending lines
}

int cogui::themes::cursive::minimum_button_height(const cogui::button&)
{
    return 2; // topline = 0 + text = 1 + bottomline = 2
}

int cogui::themes::cursive::minimum_window_width(const cogui::window &w)
{
    return w.getTitle().length() + (w.getTitle().length() > 0? WND_TITLE_DELIM_LEFT.length() + WND_TITLE_DELIM_RIGHT.length() : 0) +
            (w.hasSysmenuButton() ? WND_SYSMENU.length() : 0) +
            (w.hasMaximizeButton()? WND_MAXIMIZE.length() : 0) +
            (w.hasCloseButton() ? WND_CLOSE.length() : 0)
            ;
}

int cogui::themes::cursive::minimum_window_height(const cogui::window &)
{
    return 3; // top line + content line + bottomline
}

std::string cogui::themes::cursive::name()
{
    return "cursive";
}
