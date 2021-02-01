#include "cursive.h"
#include "cogui.h"

#include <variant>
#include <algorithm>

extern "C" cogui::theme* create()
{
    return static_cast<cogui::theme*>(new cogui::themes::cursive);
}

void cogui::themes::cursive::clear(const cogui::control &c)
{
    cogui::graphics()->clear_area(c.getX(), c.getY(), c.getWidth() + 2, c.getHeight());
}

void cogui::themes::cursive::draw_window(const cogui::window &w)
{
    if(!w.is_visible())
    {
        return;
    }

    bool rs = w.getDrawState() == window::draw_state::normal; // resizing the window?
    int drawY = w.getY();
    int drawX = w.getX();
    int drawHeight = w.getHeight();
    int drawWidth = w.getWidth();

    // depending whether this window is in resize mode or not we pick different border characters
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
    cogui::graphics()->draw_text(drawX, drawY, ul_corner_char + cogui::utils::repeated(drawWidth, line_char) + ur_corner_char);

    // bottom line
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, ll_corner_char + cogui::utils::repeated(drawWidth, line_char) +
        (w.resizeable() ? WND_LR_RESIZE : lr_corner_char) );

    // side lines
    for(int i=1; i< drawHeight; i++)
    {
        cogui::graphics()->draw_text(drawX, drawY + i, vert_line_char);
        cogui::graphics()->draw_text(drawX + drawWidth + 1, drawY + i, vert_line_char);
    }

    int available_width = drawWidth; // -3 because of the begin and end chars for title separator

    int close_pos = -1;
    int sysmenu_pos = -1;
    int maximize_pos = -1;

    // if there is a close button
    if(w.hasCloseButton())
    {
        available_width -= close_char.length();
        log_debug() << "adjusting width due to close button:" << drawWidth << " avail:" << available_width;
        cogui::graphics()->draw_text(drawX + available_width, drawY, close_char);
        close_pos = drawX + available_width + 1;

    }

    // if there is a maximize button
    if(w.hasMaximizeButton())
    {
        available_width -= maximize_char.length() - 1;
        log_debug() << "adjusting width due to maximize button:" <<drawWidth << " avail:" << available_width;

        cogui::graphics()->draw_text(drawX + available_width , drawY, maximize_char);
        maximize_pos = drawX + available_width + 1;
        if(w.hasCloseButton()) // remove ugly close and end buttons from window titlebar
        {
            int newx = drawX + available_width + maximize_char.length() - 1;
            cogui::graphics()->draw_text(newx, drawY, L" ");
        }
    }

    // if there is a system menu
    if(w.hasSysmenuButton())
    {
        available_width -= sysmenu_char.length();
        log_debug() << "adjusting width due to sysmenu button:" <<drawWidth << " avail:" << available_width;

        cogui::graphics()->draw_text(drawX + 1, drawY, w.getSystemMenu().isOpened() ? WND_SYSMENU_DOWN : sysmenu_char);
        sysmenu_pos = drawX + 1 + 1 ;
    }

    // title
    if(!w.getTitle().empty())
    {
        std::wstring wtitle = w.getTitle();
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = drawX + available_width / 2 - (wtitle.length() +1) / 2;

        std::wstring t = title_delim_left_char + wtitle + title_delim_right_char;

        cogui::graphics()->draw_text(lefts, drawY, t);
    }

    // tell the window the position of the three topbar buttons
    w.update_titlebar_btn_positions(close_pos, sysmenu_pos, maximize_pos);

    // do we have a menubar
    if(w.hasMenubar())
    {
        cogui::graphics()->draw_text(drawX, drawY + 2, (rs ? WND_VERT_MENULINE_START_RESIZE : WND_VERT_MENULINE_START)
                                              + cogui::utils::repeated(drawWidth, WND_HORZ_MENULINE)
                                              + (rs ? WND_VERT_MENULINE_END_RESIZE : WND_VERT_MENULINE_END)
                    );
        auto& m = const_cast<cogui::menubar&>(const_cast<cogui::window&>(w).get_main_menu());
        auto& items = m.items();
        int mdix = drawX + 2;
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
                mdix =  drawX + drawWidth - accumulated_width;
            }
            else
            {
                cogui::graphics()->draw_title(mdix, drawY + 1, itm.caption(), cogui::textflags::bold);
                const_cast<cogui::window&>(w).update_menubar_positions(&itm, {mdix, drawY + 1}, {mdix + itm.caption().length(), drawY + 1});
                mdix += (itm.caption().length());
            }
        }
    }


    // and the scrollbar, finally
    switch(w.get_scrollbar().get_orientation())
    {
    case cogui::scrollbar::orientation::so_none:
        break;

    case cogui::scrollbar::orientation::so_horizontal:
        draw_scrollbar(w.get_horizontal_scrollbar());
        break;

    case cogui::scrollbar::orientation::so_both:
        draw_scrollbar(w.get_horizontal_scrollbar());
        draw_scrollbar(w.get_vertical_scrollbar());
        break;

    case cogui::scrollbar::orientation::so_vertical:
        draw_scrollbar(w.get_vertical_scrollbar());
        break;
    }

}

void cogui::themes::cursive::draw_button(const cogui::button &b)
{
    if(!b.is_visible())
    {
        return;
    }

    // picking the right characters, since a button can have three states: normal, focuses, pressed
    auto ul_char = BTN_UL_CORNER_STATE_UP ;
    auto ll_char = BTN_LL_CORNER_STATE_UP ;
    auto ur_char = BTN_UR_CORNER_STATE_UP ;
    auto lr_char = BTN_LR_CORNER_STATE_UP ;
    auto top_char = BTN_TOP_BORDER_UP ;
    auto bottom_char = BTN_BOTTOM_BORDER_UP ;
    auto left_border = BTN_LEFT_UP ;
    auto right_border = BTN_RIGHT_UP ;

    if(b.get_focus_state() == cogui::control::focus_state::focused)
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

    if(b.get_press_state() == control::press_state::pressed)
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

    int drawX = b.getX();
    int drawY = b.getY();
    int drawWidth = b.getWidth();
    int drawHeight = b.getHeight();

    // top line
    cogui::graphics()->draw_text(drawX, drawY, ul_char + cogui::utils::repeated(drawWidth - 1, top_char ) + ur_char);

    // bottom line
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, ll_char + cogui::utils::repeated(drawWidth - 1, bottom_char ) + lr_char);

    // side lines
    for(int i=1; i< drawHeight; i++)
    {
        cogui::graphics()->draw_text(drawX, drawY + i, left_border);
        cogui::graphics()->draw_text(drawX + drawWidth, drawY + i, right_border);
    }

    // button text. Will be replaced with "..." if text is too long for the actual button size
    int title_x = (int)(drawX + drawWidth / 2 - b.getTitle().length() / 2);
    std::wstring title_to_draw = b.getTitle();
    if(title_x <= drawX)
    {
        title_x = drawX + 1;
    }

    log_debug() << "Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << drawWidth;
    if(static_cast<int>(title_to_draw.length()) >= drawWidth)
    {
        if(drawWidth <= 5)
        {
            title_to_draw = title_to_draw[0];
            while(static_cast<int>(title_to_draw.length()) < drawWidth - 2 && title_to_draw.length() < cogui::MAX_CAPTION_WIDTH)
            {
                title_to_draw += L".";
            }
        }
        else
        {
            title_to_draw = title_to_draw.substr(0, drawWidth - 4) + L"...";
        }
        log_debug() << "Overriding Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << drawWidth;
    }

    if(drawHeight >= 2)
    {
        int title_y = drawY + drawHeight / 2;
        cogui::graphics()->draw_text(drawX + 1, title_y, cogui::utils::repeated(drawWidth - 2, L" "));
        if(b.get_focus_state() == cogui::control::focus_state::focused)
        {
            log_debug()<<"button is focused, drawing underlined";
            cogui::graphics()->draw_title(title_x, title_y, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
        }
        else
        {
            cogui::graphics()->draw_title(title_x, title_y, title_to_draw);
        }
    }
}

void cogui::themes::cursive::draw_menu(const cogui::menu &m)
{
    int drawY = m.getY();
    int drawHeight = m.getHeight();
    int drawX = m.getX();
    int drawWidth = m.getWidth();

    bool one_is_selectable = false;
    // see if there is a menu action which is selectable or not
    for(int i=0; i<m.get_action_count(); i++)
    {
        if(m[i].isSelectable())
        {
            one_is_selectable = true;
            break;
        }
    }

    log_debug() << (one_is_selectable ? "ONE_IS_SELECTABLE" : "NO SELECTABLES");

    cogui::graphics()->clear_area(drawX, drawY, drawWidth, drawHeight);

    cogui::graphics()->draw_text(drawX, drawY, MNU_UL_CORNER);
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, MNU_LL_CORNER);
    cogui::graphics()->draw_text(drawX + drawWidth, drawY, MNU_UR_CORNER);
    cogui::graphics()->draw_text(drawX + drawWidth, drawY + drawHeight, MNU_LR_CORNER);
    cogui::graphics()->draw_text(drawX + 1, drawY + drawHeight, cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL));

    if(m.isSysmenu())
    {
        cogui::graphics()->draw_text(drawX + 1, drawY, cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL));
    }
    else
    {
        cogui::graphics()->draw_text(drawX , drawY,  MNU_UR_CORNER + cogui::utils::repeated(drawWidth - 1, L" ") + MNU_UL_CORNER + MNU_HORIZONTAL);
    }

    if(m.isSysmenu())
    {
        cogui::graphics()->draw_text(drawX, drawY, MNU_SYSMENU_TOP);
    }

    int mc = 0;
    for(int y = drawY+1; y < drawY + drawHeight; y++)
    {
        cogui::graphics()->draw_text(drawX, y, MNU_VERTICAL);
        cogui::graphics()->draw_text(drawX + drawWidth, y, MNU_VERTICAL);
        log_debug() << "menu LASTSEL:" << m.getLastSelectedIndex() << " mc=" << mc;

        std::wstring titleToDraw = m[mc].getTitle();

        if(m[mc].isSelectable())
        {
            titleToDraw = CHK_UNCHECKED + MNU_EMPTY_CHAR + MNU_EMPTY_CHAR + titleToDraw;
        }
        else if (titleToDraw != cogui::menu::separator_item.getTitle() && one_is_selectable)
        {
            titleToDraw = MNU_EMPTY_CHAR + MNU_EMPTY_CHAR + MNU_EMPTY_CHAR +titleToDraw;
        }

        if(titleToDraw == cogui::menu::separator_item.getTitle())
        {
            cogui::graphics()->draw_text(drawX, y, MNU_LEFT_SEPARATOR + cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL)  + MNU_RIGHT_SEPARATOR);
        }
        else
        {
            while(static_cast<int>(titleToDraw.length()) < drawWidth - 1 && titleToDraw.length() < cogui::MAX_CAPTION_WIDTH) titleToDraw += L" ";

            if(mc == m.getLastSelectedIndex())
            {
                cogui::graphics()->set_colors(graphics_engine::color::black, graphics_engine::color::white);
                cogui::graphics()->draw_title(drawX + 1, y, titleToDraw);
                cogui::graphics()->set_colors(graphics_engine::color::white, graphics_engine::color::black);
            }
            else
            {
                cogui::graphics()->draw_title(drawX + 1, y, titleToDraw);
            }

        }
        mc ++;
        if(mc >= m.get_action_count())
        {
            log_warning() << "an action counter passed over the menu";
            break;
        }
    }
}

void cogui::themes::cursive::draw_checkbox(const checkbox &c)
{
    if(!c.is_visible())
    {
        return;
    }

    int drawX = c.getX();

    int titleX = (int)(drawX + c.getWidth() / 2 - c.getTitle().length() / 2);

    if(titleX <= drawX + 2)
    {
        titleX = drawX + 4;
    }

    std::wstring title_to_draw = c.getTitle();

    if(static_cast<int>(title_to_draw.length()) >= c.getWidth() - 4)
    {
        title_to_draw = title_to_draw.substr(0, c.getWidth() - 4 - 4) + L"...";
    }

    int drawY = c.getY() + c.getHeight() / 2;

    if(c.get_focus_state() == cogui::control::focus_state::focused)
    {
        cogui::graphics()->draw_text(drawX, drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::underline & cogui::textflags::bold);
        cogui::graphics()->draw_title(titleX, drawY, title_to_draw, cogui::textflags::underline & cogui::textflags::bold);
    }
    else
    {
        cogui::graphics()->draw_text(drawX, drawY, c.checked() ? CHK_CHECKED : CHK_UNCHECKED, cogui::textflags::normal);
        cogui::graphics()->draw_title(titleX, drawY, title_to_draw);
    }
}

void cogui::themes::cursive::draw_scrollbar(const scrollbar &s)
{
    control* c = s.get_parent();
    if(!c)
    {
        return;
    }

    // do we have a vertical scrollbar?
    if(s.get_orientation() == scrollbar::orientation::so_vertical)
    {
        draw_verticall_scrollbar(c, const_cast<scrollbar&>(s));
    }

    // do we have a horizontal scrollbar?
    if(s.get_orientation() == scrollbar::orientation::so_horizontal)
    {
        draw_horizontal_scrollbar(c, const_cast<scrollbar&>(s));
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

int cogui::themes::cursive::first_available_row(const cogui::window &w)
{
    if(w.hasMenubar()) return 3;
    return 1;
}

std::string cogui::themes::cursive::name()
{
    return "cursive";
}

void cogui::themes::cursive::draw_horizontal_scrollbar(cogui::control *c, cogui::scrollbar &s)
{
    int x = c->getX();
    int h = c->getHeight();
    int w = c->getWidth();
    int y = c->getY();
    cogui::graphics()->set_bg_color(graphics_engine::color::white);

    cogui::graphics()->draw_text(x + 1, y + h, SCROLL_LEFT_ARROW, cogui::textflags::normal);
    s.set_dec_arrow_screen_position({x + 1, y + h, 1, 1});

    cogui::graphics()->draw_text(x + w, y + h, SCROLL_RIGHT_ARROW, cogui::textflags::normal);
    s.set_inc_arrow_screen_position({x + w, y + h, 1, 1});

    int handle_counter = 0;

    for(int i =x + 2; i<= x + w - 1; i++)
    {
        cogui::graphics()->draw_text(i, y+h, SCROLL_HORIZONTAL_BODY, cogui::textflags::normal);
        if(handle_counter == s.get_handle_position())
        {
            cogui::graphics()->draw_text(i, y+h, SCROLL_HORIZONTAL_HANDLE, cogui::textflags::normal);
        }
        handle_counter ++;
    }
    cogui::graphics()->set_bg_color(graphics_engine::color::black);
}

void cogui::themes::cursive::draw_verticall_scrollbar(cogui::control *c, cogui::scrollbar &s)
{
    int x = c->getX();
    int w = c->getWidth();
    int y = c->getY() + c->first_available_row(); // no need to draw scrollbar on menu
    int h = c->getHeight() - c->first_available_row() - 1;
    cogui::graphics()->set_bg_color(graphics_engine::color::white);

    cogui::graphics()->draw_text(x + w + 1, y, SCROLL_UP_ARROW, cogui::textflags::normal);
    s.set_dec_arrow_screen_position({x + w + 1, y, 1 ,1});

    cogui::graphics()->draw_text(x + w + 1, y + h, SCROLL_DOWN_ARROW, cogui::textflags::normal);
    s.set_inc_arrow_screen_position({x + w + 1, y + h, 1, 1});

    int handle_counter = 0;
    for(int i=y + 1; i<y+h; i++)
    {
        cogui::graphics()->draw_text(x + w + 1, i, SCROLL_VERTICAL_BODY, cogui::textflags::normal);
        if(handle_counter == s.get_handle_position())
        {
            cogui::graphics()->draw_text(x + w + 1, i, SCROLL_VERTICAL_HANDLE, cogui::textflags::normal);
        }
        handle_counter ++;
    }
    cogui::graphics()->set_bg_color(graphics_engine::color::black);
}
