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
    cogui::graphics()->clear_area(c.get_x(), c.get_y(), c.get_width() + 2, c.get_height());
}

void cogui::themes::cursive::draw_window(const cogui::window &w)
{
    if(!w.is_visible())
    {
        return;
    }

    bool normal_state = w.get_draw_state() == window::draw_state::normal; // resizing the window?
    bool active_state = w.is_active();

    int drawY = w.get_y();
    int drawX = w.get_x();
    int drawHeight = w.get_height();
    int drawWidth = w.get_width();

    std::wstring empty_line = cogui::utils::repeated(drawWidth + 1, L" ");
    // clear the window
    for(int y=0; y<drawHeight; y++)
    {
        cogui::graphics()->draw_text(drawX, drawY + y, empty_line.c_str());
    }

    // depending whether this window is in resize mode or not we pick different border characters
    auto line_char = normal_state ? active_state ? WND_HORZ_LINE : HORZ_LINE_RESIZE : HORZ_LINE_RESIZE;
    auto vert_line_char = normal_state ? active_state ? WND_VERT_LINE : VERT_LINE_RESIZE : VERT_LINE_RESIZE;
    auto ul_corner_char = normal_state ? active_state ? WND_UL_CORNER : UL_CORNER_RESIZE : UL_CORNER_RESIZE;
    auto ur_corner_char = normal_state ? active_state ? WND_UR_CORNER : UR_CORNER_RESIZE : UR_CORNER_RESIZE;
    auto ll_corner_char = normal_state ? active_state ? WND_LL_CORNER : LL_CORNER_RESIZE : LL_CORNER_RESIZE;
    auto lr_corner_char = normal_state ? active_state ? WND_LR_CORNER : LR_CORNER_RESIZE : LR_CORNER_RESIZE;
    auto sysmenu_char = normal_state ? active_state ? WND_SYSMENU : WND_SYSMENU_RESIZE : WND_SYSMENU_RESIZE;
    auto title_delim_left_char = normal_state ? active_state ? WND_TITLE_DELIM_LEFT : WND_TITLE_DELIM_LEFT_RESIZE : WND_TITLE_DELIM_LEFT_RESIZE;
    auto title_delim_right_char = normal_state ? active_state ? WND_TITLE_DELIM_RIGHT : WND_TITLE_DELIM_RIGHT_RESIZE : WND_TITLE_DELIM_RIGHT_RESIZE;
    auto close_char = normal_state ? active_state ? WND_CLOSE : WND_CLOSE_RESIZE : WND_CLOSE_RESIZE;
    auto maximize_char = normal_state ? active_state ? WND_MAXIMIZE : WND_MAXIMIZE_RESIZE : WND_MAXIMIZE_RESIZE;

    // top line
    cogui::graphics()->draw_text(drawX, drawY, std::wstring(ul_corner_char + cogui::utils::repeated(drawWidth, line_char) + ur_corner_char).c_str() );

    // bottom line
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, std::wstring(ll_corner_char + cogui::utils::repeated(drawWidth, line_char) +
        (w.is_resizeable() ? WND_LR_RESIZE : lr_corner_char)).c_str() );

    // side lines
    for(int i=1; i< drawHeight; i++)
    {
        cogui::graphics()->draw_text(drawX, drawY + i, vert_line_char.c_str());
        cogui::graphics()->draw_text(drawX + drawWidth + 1, drawY + i, vert_line_char.c_str());
    }

    int available_width = drawWidth; // -3 because of the begin and end chars for title separator

    int close_pos = -1;
    int sysmenu_pos = -1;
    int maximize_pos = -1;

    // if there is a close button
    if(w.has_close_button())
    {
        available_width -= close_char.length();
//        log_debug() << "adjusting width due to close button:" << drawWidth << " avail:" << available_width;
        cogui::graphics()->draw_text(drawX + available_width, drawY, close_char.c_str());
        close_pos = drawX + available_width + 1;

    }

    // if there is a maximize button
    if(w.has_maximize_button())
    {
        available_width -= maximize_char.length() - 1;
//        log_debug() << "adjusting width due to maximize button:" <<drawWidth << " avail:" << available_width;

        cogui::graphics()->draw_text(drawX + available_width , drawY, maximize_char.c_str());
        maximize_pos = drawX + available_width + 1;
        if(w.has_close_button()) // remove ugly close and end buttons from window titlebar
        {
            int newx = drawX + available_width + maximize_char.length() - 1;
            cogui::graphics()->draw_text(newx, drawY, L" ");
        }
    }

    // if there is a system menu
    if(w.has_sysmenu_button())
    {
        available_width -= sysmenu_char.length();
//        log_debug() << "adjusting width due to sysmenu button:" <<drawWidth << " avail:" << available_width;

        cogui::graphics()->draw_text(drawX + 1, drawY, (w.get_system_menu().isOpened() ? WND_SYSMENU_DOWN : sysmenu_char).c_str());
        sysmenu_pos = drawX + 1 + 1 ;
    }

    // title
    if(!w.get_title().empty())
    {
        std::wstring wtitle = w.get_title();
        available_width -= title_delim_left_char.length() + title_delim_right_char.length(); // two title delimiters
        int lefts = drawX + available_width / 2 - (wtitle.length() +1) / 2;

        std::wstring t = title_delim_left_char + wtitle + title_delim_right_char;

        cogui::graphics()->draw_text(lefts, drawY, t.c_str());
    }

    // tell the window the position of the three topbar buttons
    m_close_button_positions[&w] = rect {close_pos, drawY, 1, 1};
    m_sysmenu_button_positions[&w] = rect {sysmenu_pos, drawY, 1, 1};
    m_maximize_button_positions[&w] = rect {maximize_pos, drawY, 1, 1};

    // do we have a menubar
    if(w.has_menubar())
    {
        cogui::graphics()->draw_text(drawX, drawY + 2, ((normal_state ? active_state ? WND_VERT_MENULINE_START_RESIZE : WND_VERT_MENULINE_START:WND_VERT_MENULINE_START )
                                              + cogui::utils::repeated(drawWidth, WND_HORZ_MENULINE)
                                              + (normal_state ? active_state ?WND_VERT_MENULINE_END_RESIZE : WND_VERT_MENULINE_END: WND_VERT_MENULINE_END)).c_str()
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
                cogui::graphics()->draw_text(mdix, drawY + 1, itm.caption().c_str(), cogui::textflags::title & cogui::textflags::bold);
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

    int drawX = b.get_x();
    int drawY = b.get_y();
    int drawWidth = b.get_width();
    int drawHeight = b.get_height();

    // top line
    cogui::graphics()->draw_text(drawX, drawY, (ul_char + cogui::utils::repeated(drawWidth - 1, top_char ) + ur_char).c_str());

    // bottom line
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, (ll_char + cogui::utils::repeated(drawWidth - 1, bottom_char ) + lr_char).c_str());

    // side lines
    for(int i=1; i< drawHeight; i++)
    {
        cogui::graphics()->draw_text(drawX, drawY + i, left_border.c_str());
        cogui::graphics()->draw_text(drawX + drawWidth, drawY + i, right_border.c_str());
    }

    // button text. Will be replaced with "..." if text is too long for the actual button size
    int title_x = (int)(drawX + drawWidth / 2 - b.get_title().length() / 2);
    std::wstring title_to_draw = b.get_title();
    if(title_x <= drawX)
    {
        title_x = drawX + 1;
    }

//    log_debug() << "Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << drawWidth;
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
//        log_debug() << "Overriding Btn:" << title_to_draw << "TTL.length:" << title_to_draw.length() << "B.widh:" << drawWidth;
    }

    if(drawHeight >= 2)
    {
        int title_y = drawY + drawHeight / 2;
        cogui::graphics()->draw_text(drawX + 1, title_y, cogui::utils::repeated(drawWidth - 2, L" ").c_str());
        if(b.get_focus_state() == cogui::control::focus_state::focused)
        {
//            log_debug()<<"button is focused, drawing underlined";
            cogui::textflags f = cogui::textflags::title;
            f = f & cogui::textflags::underline;
            f = f & cogui::textflags::bold;
            cogui::graphics()->draw_text(title_x, title_y, title_to_draw.c_str(), f);
        }
        else
        {
            cogui::graphics()->draw_text(title_x, title_y, title_to_draw.c_str(), cogui::textflags::title);
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
        if(m[i].is_checkable())
        {
            one_is_selectable = true;
            break;
        }
    }

//    log_debug() << (one_is_selectable ? "ONE_IS_SELECTABLE" : "NO SELECTABLES");

    cogui::graphics()->clear_area(drawX, drawY, drawWidth, drawHeight);

    cogui::graphics()->draw_text(drawX, drawY, MNU_UL_CORNER.c_str());
    cogui::graphics()->draw_text(drawX, drawY + drawHeight, MNU_LL_CORNER.c_str());
    cogui::graphics()->draw_text(drawX + drawWidth, drawY, MNU_UR_CORNER.c_str());
    cogui::graphics()->draw_text(drawX + drawWidth, drawY + drawHeight, MNU_LR_CORNER.c_str());
    cogui::graphics()->draw_text(drawX + 1, drawY + drawHeight, cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL).c_str());

    if(m.isSysmenu())
    {
        cogui::graphics()->draw_text(drawX + 1, drawY, cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL).c_str());
    }
    else
    {
        cogui::graphics()->draw_text(drawX , drawY, (MNU_UR_CORNER + cogui::utils::repeated(drawWidth - 1, L" ") + MNU_UL_CORNER + MNU_HORIZONTAL).c_str());
    }

    if(m.isSysmenu())
    {
        cogui::graphics()->draw_text(drawX, drawY, MNU_SYSMENU_TOP.c_str());
    }

    int mc = 0;
    for(int y = drawY+1; y < drawY + drawHeight; y++)
    {
        cogui::graphics()->draw_text(drawX, y, MNU_VERTICAL.c_str());
        cogui::graphics()->draw_text(drawX + drawWidth, y, MNU_VERTICAL.c_str());
//        log_debug() << "menu LASTSEL:" << m.getLastSelectedIndex() << " mc=" << mc;

        std::wstring titleToDraw = m[mc].get_title();

        if(m[mc].is_checkable())
        {
            titleToDraw = (m[mc].is_checked() ? CHK_CHECKED : CHK_UNCHECKED) + MNU_EMPTY_CHAR + MNU_EMPTY_CHAR + titleToDraw;
        }
        else if (titleToDraw != cogui::menu::separator_item.get_title() && one_is_selectable)
        {
            titleToDraw = MNU_EMPTY_CHAR + MNU_EMPTY_CHAR + MNU_EMPTY_CHAR +titleToDraw;
        }

        if(titleToDraw == cogui::menu::separator_item.get_title())
        {
            cogui::graphics()->draw_text(drawX, y, (MNU_LEFT_SEPARATOR + cogui::utils::repeated(drawWidth - 1, MNU_HORIZONTAL)  + MNU_RIGHT_SEPARATOR).c_str());
        }
        else
        {
            while(static_cast<int>(titleToDraw.length()) < drawWidth - 1 && titleToDraw.length() < cogui::MAX_CAPTION_WIDTH) titleToDraw += L" ";

            if(mc == m.getLastSelectedIndex())
            {
                cogui::graphics()->set_colors(color::black, color::white);
                cogui::graphics()->draw_text(drawX + 1, y, titleToDraw.c_str(), cogui::textflags::title);
                cogui::graphics()->set_colors(color::white, color::black);
            }
            else
            {
                cogui::graphics()->draw_text(drawX + 1, y, titleToDraw.c_str(), cogui::textflags::title);
            }

        }
        mc ++;
        if(mc >= m.get_action_count())
        {
//            log_warning() << "an action counter passed over the menu";
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

    int drawX = c.get_x();

    int titleX = (int)(drawX + c.get_width() / 2 - c.get_title().length() / 2);

    if(titleX <= drawX + 2)
    {
        titleX = drawX + 4;
    }

    std::wstring title_to_draw = c.get_title();

    if(static_cast<int>(title_to_draw.length()) >= c.get_width() - 4)
    {
        title_to_draw = title_to_draw.substr(0, c.get_width() - 4 - 4) + L"...";
    }

    int drawY = c.get_y() + c.get_height() / 2;

    if(c.get_focus_state() == cogui::control::focus_state::focused)
    {
        cogui::graphics()->draw_text(drawX, drawY, (c.checked() ? CHK_CHECKED : CHK_UNCHECKED).c_str(), cogui::textflags::underline & cogui::textflags::bold);
        cogui::graphics()->draw_text(titleX, drawY, title_to_draw.c_str(), cogui::textflags::title && cogui::textflags::underline & cogui::textflags::bold);
    }
    else
    {
        cogui::graphics()->draw_text(drawX, drawY, (c.checked() ? CHK_CHECKED : CHK_UNCHECKED).c_str(), cogui::textflags::normal);
        cogui::graphics()->draw_text(titleX, drawY, title_to_draw.c_str(), cogui::textflags::title);
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
    return c.get_title().length() + 2; // +2 for the checkmarek followed by a space
}

int cogui::themes::cursive::minimum_checkbox_height(const cogui::checkbox &)
{
    return 1;
}

int cogui::themes::cursive::minimum_button_width(const cogui::button &b)
{
    return b.get_title().length() + 2; // +2 for the beginning and ending lines
}

int cogui::themes::cursive::minimum_button_height(const cogui::button&)
{
    return 2; // topline = 0 + text = 1 + bottomline = 2
}

int cogui::themes::cursive::minimum_window_width(const cogui::window &w)
{
    return w.get_title().length() + (w.get_title().length() > 0? WND_TITLE_DELIM_LEFT.length() + WND_TITLE_DELIM_RIGHT.length() : 0) +
            (w.has_sysmenu_button() ? WND_SYSMENU.length() : 0) +
            (w.has_maximize_button()? WND_MAXIMIZE.length() : 0) +
            (w.has_close_button() ? WND_CLOSE.length() : 0)
            ;
}

int cogui::themes::cursive::minimum_window_height(const cogui::window &)
{
    return 3; // top line + content line + bottomline
}

int cogui::themes::cursive::first_available_row(const cogui::window &w)
{
    if(w.has_menubar()) return 3;
    return 1;
}

cogui::rect cogui::themes::cursive::close_button_pos(const cogui::window &w)
{
    if(m_close_button_positions.count(&w) != 0)
    {
        return m_close_button_positions[&w];
    }
    return {};
}

cogui::rect cogui::themes::cursive::sysmenu_button_pos(const cogui::window &w)
{
    if(m_sysmenu_button_positions.count(&w) != 0)
    {
        return m_sysmenu_button_positions[&w];
    }
    return {};

}

cogui::rect cogui::themes::cursive::maximize_button_pos(const cogui::window &w)
{
    if(m_maximize_button_positions.count(&w) != 0)
    {
        return m_maximize_button_positions[&w];
    }
    return {};

}

std::string cogui::themes::cursive::name()
{
    return "cursive";
}

void cogui::themes::cursive::draw_horizontal_scrollbar(cogui::control *c, cogui::scrollbar &s)
{
    int x = c->get_x();
    int h = c->get_height();
    int w = c->get_width();
    int y = c->get_y();
    cogui::graphics()->set_bg_color(color::white);

    cogui::graphics()->draw_text(x + 1, y + h, SCROLL_LEFT_ARROW.c_str(), cogui::textflags::normal);
    s.set_dec_arrow_screen_position({x + 1, y + h, 1, 1});

    cogui::graphics()->draw_text(x + w, y + h, SCROLL_RIGHT_ARROW.c_str(), cogui::textflags::normal);
    s.set_inc_arrow_screen_position({x + w, y + h, 1, 1});

    int handle_counter = 0;

    for(int i =x + 2; i<= x + w - 1; i++)
    {
        cogui::graphics()->draw_text(i, y+h, SCROLL_HORIZONTAL_BODY.c_str(), cogui::textflags::normal);
        if(handle_counter == s.get_handle_position())
        {
            cogui::graphics()->draw_text(i, y+h, SCROLL_HORIZONTAL_HANDLE.c_str(), cogui::textflags::normal);
            s.set_handle_screen_position({i, y+h, 1, 1});
        }
        handle_counter ++;
    }
    cogui::graphics()->set_bg_color(color::black);
}

void cogui::themes::cursive::draw_verticall_scrollbar(cogui::control *c, cogui::scrollbar &s)
{
    int x = c->get_x();
    int w = c->get_width();
    int y = c->get_y() + c->first_available_row(); // no need to put the scrollbar on menu
    int h = c->get_height() - c->first_available_row() - 1;
    cogui::graphics()->set_bg_color(color::white);

    cogui::graphics()->draw_text(x + w + 1, y, SCROLL_UP_ARROW.c_str(), cogui::textflags::normal);
    s.set_dec_arrow_screen_position({x + w + 1, y, 1 ,1});

    cogui::graphics()->draw_text(x + w + 1, y + h, SCROLL_DOWN_ARROW.c_str(), cogui::textflags::normal);
    s.set_inc_arrow_screen_position({x + w + 1, y + h, 1, 1});

    int handle_counter = 0;
    for(int i=y + 1; i<y+h; i++)
    {
        cogui::graphics()->draw_text(x + w + 1, i, SCROLL_VERTICAL_BODY.c_str(), cogui::textflags::normal);
        if(handle_counter == s.get_handle_position())
        {
            cogui::graphics()->draw_text(x + w + 1, i, SCROLL_VERTICAL_HANDLE.c_str(), cogui::textflags::normal);
            s.set_handle_screen_position({x + w + 1, i, 1, 1});
        }
        handle_counter ++;
    }
    cogui::graphics()->set_bg_color(color::black);
}
