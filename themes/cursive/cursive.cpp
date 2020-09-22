#include "cursive.h"
#include "desktop.h"
#include "graphics.h"
#include "window.h"
#include "control.h"
#include "button.h"
#include "checkbox.h"

#include "log.h"
#include "utils.h"

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
        desktop::get().getGraphics()->draw_text(x, y, cogui::utils::repeated(w + 2, L" "));
    }
}

void cogui::themes::cursive::draw_window(const cogui::window &w)
{
    if(!w.isVisible())
    {
        return;
    }

    bool rs = w.getDrawState() == window::draw_state::normal;

    int drawY = w.getY();
    int drawHeight = w.getHeight();

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
    desktop::get().getGraphics()->draw_text(w.getX(), drawY, ul_corner_char + cogui::utils::repeated(w.getWidth(), line_char) + ur_corner_char);


    // bottom line
    desktop::get().getGraphics()->draw_text(w.getX(), drawY + drawHeight, ll_corner_char + cogui::utils::repeated(w.getWidth(), line_char) +
        (w.resizeable() ? WND_LR_RESIZE : lr_corner_char) );

    // side lines
    for(int i=1; i< drawHeight; i++)
    {
        desktop::get().getGraphics()->draw_text(w.getX(), drawY + i, vert_line_char);
        desktop::get().getGraphics()->draw_text(w.getX() + w.getWidth() + 1, drawY + i, vert_line_char);
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
        desktop::get().getGraphics()->draw_text(w.getX() + available_width, drawY, close_char);
        close_pos = w.getX() + available_width + 1;

    }
    if(w.hasMaximizeButton())
    {
        available_width -= maximize_char.length() - 1;
        // log_info() << "wdth:" << w.width() << " avail:" << available_width;

        desktop::get().getGraphics()->draw_text(w.getX() + available_width , drawY, maximize_char);
        maximize_pos = w.getX() + available_width + 1;
        if(w.hasCloseButton()) // remove ugly close and end buttons from window titlebar
        {
            int newx = w.getX() + available_width + maximize_char.length() - 1;
            desktop::get().getGraphics()->draw_text(newx, drawY, L" ");
        }
    }

    // if there is a system menu
    if(w.hasSysmenuButton())
    {
        available_width -= sysmenu_char.length();
        desktop::get().getGraphics()->draw_text(w.getX() + 1, drawY, w.getSystemMenu().isOpened() ? WND_SYSMENU_DOWN : sysmenu_char);
        sysmenu_pos = w.getX() + 1 + 1 ;
    }

    // title
    if(!w.getTitle().empty())
    {
        std::wstring wtitle = w.getTitle();
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = w.getX() + available_width / 2 - (wtitle.length() +1) / 2;

        std::wstring t = title_delim_left_char + wtitle + title_delim_right_char;

        desktop::get().getGraphics()->draw_text(lefts, drawY, t);
    }

    w.update_titlebar_btn_positions(close_pos, sysmenu_pos, maximize_pos);


    // do we have a menubar
    if(w.hasMenubar())
    {
        desktop::get().getGraphics()->draw_text(w.getX(), drawY + 2, (rs ? WND_VERT_MENULINE_START_RESIZE : WND_VERT_MENULINE_START)
                                              + cogui::utils::repeated(w.getWidth(), WND_HORZ_MENULINE)
                                              + (rs ? WND_VERT_MENULINE_END_RESIZE : WND_VERT_MENULINE_END)
                    );
        auto& m = const_cast<cogui::menubar&>(const_cast<cogui::window&>(w).getMainMenu());
        auto& items = m.items();
        int mdix = w.getX() + 2;
        for(size_t i = 0; i < items.size(); i++)
        {
            menu& itm = const_cast<cogui::menu&>(items[i]);
            if(itm.caption() == cogui::menubar::align_right_after.caption())
            {
                size_t accumulated_width = 0;
                for(size_t j=i+1; j<items.size(); j++)
                {
                    menu& itmj = const_cast<cogui::menu&>(items[j]);
                    accumulated_width += itmj.caption().length();
                }
                mdix =  w.getX() + w.getWidth() - accumulated_width;
            }
            else
            {
                desktop::get().getGraphics()->draw_title(mdix, drawY + 1, itm.caption(), cogui::textflags::bold);
                const_cast<cogui::window&>(w).update_menubar_positions(&itm, {mdix, drawY + 1}, {mdix + itm.caption().length(), drawY + 1});
                mdix += (itm.caption().length());
            }
        }
    }

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
    desktop::get().getGraphics()->draw_text(b.getX(), b.getY(), ul_char);
    desktop::get().getGraphics()->draw_text(b.getX(), b.getY() + b.getHeight(), ll_char);
    desktop::get().getGraphics()->draw_text(b.getX() + b.getWidth(), b.getY(), ur_char);
    desktop::get().getGraphics()->draw_text(b.getX() + b.getWidth(), b.getY() + b.getHeight(), lr_char);

    // top border of button
    desktop::get().getGraphics()->draw_text(b.getX() + 1, b.getY(), cogui::utils::repeated(b.getWidth() - 1, top_char ) );
    desktop::get().getGraphics()->draw_text(b.getX() + 1, b.getY() + b.getHeight(), cogui::utils::repeated(b.getWidth() - 1, bottom_char) );

    // side lines
    for(int i=1; i< b.getHeight(); i++)
    {
        desktop::get().getGraphics()->draw_text(b.getX(), b.getY() + i, left_border);
        desktop::get().getGraphics()->draw_text(b.getX() + b.getWidth(), b.getY() + i, right_border);
    }

    // button text
    int title_x = (int)(b.getX() + b.getWidth() / 2 - b.getTitle().length() / 2);
    std::wstring title_to_draw = b.getTitle();
    if(title_x <= b.getX())
    {
        title_x = b.getX() + 1;
    }

//    log_info() << "Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << b.getWidth();
    if(static_cast<int>(title_to_draw.length()) >= b.getWidth())
    {
        if(b.getWidth() <= 5)
        {
            title_to_draw = title_to_draw[0];
            while(static_cast<int>(title_to_draw.length()) < b.getWidth() - 2 && title_to_draw.length() < 8192)
            {
                title_to_draw += L".";
            }
        }
        else
        {
            title_to_draw = title_to_draw.substr(0, b.getWidth() - 4) + L"...";
        }
//        log_info() << "Overriding Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << b.getWidth();
    }

    if(b.getHeight() >= 2)
    {
        int title_y = b.getY() + b.getHeight() / 2;
        desktop::get().getGraphics()->draw_text(b.getX() + 1, title_y, cogui::utils::repeated(b.getWidth() - 2, L" "));
        if(b.getFocusState() == cogui::control::focus_state::focused)
        {
            // log_info()<<"focused, drawing underlined";
            desktop::get().getGraphics()->draw_title(title_x, title_y, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
        }
        else
        {
            desktop::get().getGraphics()->draw_title(title_x, title_y, title_to_draw);
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
        desktop::get().getGraphics()->draw_text(x, y, cogui::utils::repeated(wi + 2, L" "));
    }

    desktop::get().getGraphics()->draw_text(m.getX(), m.getY(), MNU_UL_CORNER);
    desktop::get().getGraphics()->draw_text(m.getX(), m.getY() + m.getHeight(), MNU_LL_CORNER);
    desktop::get().getGraphics()->draw_text(m.getX() + m.getWidth(), m.getY(), MNU_UR_CORNER);
    desktop::get().getGraphics()->draw_text(m.getX() + m.getWidth(), m.getY() + m.getHeight(), MNU_LR_CORNER);
    desktop::get().getGraphics()->draw_text(m.getX() + 1, m.getY() + m.getHeight(), cogui::utils::repeated(m.getWidth() - 1, MNU_HORIZONTAL));

    if(m.isSysmenu())
    {
        desktop::get().getGraphics()->draw_text(m.getX() + 1, m.getY(), cogui::utils::repeated(m.getWidth() - 1, MNU_HORIZONTAL));
    }
    else
    {
        desktop::get().getGraphics()->draw_text(m.getX() , m.getY(),  MNU_UR_CORNER + cogui::utils::repeated(m.getWidth() - 1, L" ") + MNU_UL_CORNER + MNU_HORIZONTAL);
    }

    if(m.isSysmenu())
    {
        desktop::get().getGraphics()->draw_text(m.getX(), m.getY(), MNU_SYSMENU_TOP);
    }

    int mc = 0;
    for(int y = top+1; y < top + h; y++)
    {
        desktop::get().getGraphics()->draw_text(x, y, MNU_VERTICAL);
        desktop::get().getGraphics()->draw_text(x + wi, y, MNU_VERTICAL);
        // log_info() << "LASTSEL:" << m.getLastSelectedIndex() << " mc=" << mc;

        std::wstring titleToDraw = m[mc].getTitle();
        if(titleToDraw == cogui::menu::separator_item.getTitle())
        {
            desktop::get().getGraphics()->draw_text(x, y, MNU_LEFT_SEPARATOR + cogui::utils::repeated(m.getWidth() - 1, MNU_HORIZONTAL)  + MNU_RIGHT_SEPARATOR);
        }
        else
        {
            while(static_cast<int>(titleToDraw.length()) < m.getWidth() - 1 && titleToDraw.length() < 8192) titleToDraw += L" ";

            if(mc == m.getLastSelectedIndex())
            {
                desktop::get().getGraphics()->set_colors(graphics_engine::color::black, graphics_engine::color::white);
                desktop::get().getGraphics()->draw_title(x + 1, y, titleToDraw);
                desktop::get().getGraphics()->set_colors(graphics_engine::color::white, graphics_engine::color::black);
            }
            else
            {
                desktop::get().getGraphics()->draw_title(x + 1, y, titleToDraw);
            }

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
        desktop::get().getGraphics()->draw_text(c.getX(), drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::underline & cogui::textflags::bold);
        desktop::get().getGraphics()->draw_title(title_x, drawY, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
    }
    else
    {
        desktop::get().getGraphics()->draw_text(c.getX(), drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::normal);
        desktop::get().getGraphics()->draw_title(title_x, drawY, title_to_draw);
    }
}

int cogui::themes::cursive::minimum_checkbox_width(const cogui::checkbox &c)
{
    return c.getTitle().length() + 2; // +2 for the checkmarek followed by a space
}

int cogui::themes::cursive::minimum_checkbox_height(const cogui::checkbox &)
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

