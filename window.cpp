#include "window.h"
#include "desktop.h"
#include "theme.h"
#include "action.h"

#include "log.h"

#include <memory>

cogui::window::OnResize::argument cogui::window::on_resize;
cogui::window::OnClose::argument cogui::window::on_close;
cogui::window::OnKeypress::argument cogui::window::on_keypress;
cogui::window::HotkeyT::argument cogui::window::hotkeys;
cogui::window::OnMouseDown::argument cogui::window::on_mouse_down;
cogui::window::OnMouseUp::argument cogui::window::on_mouse_up;
cogui::window::SystemMenu::argument cogui::window::sysmenu;
cogui::window::MenuBar::argument cogui::window::mainmenu;
cogui::window::ScrollBar::argument cogui::window::scrollbars;

cogui::window::~window()
{
    desktop::get().remove_window(this);
}

void cogui::window::draw() const
{
    auto t = cogui::desktop::get().getTheme();
    t->draw_window(*this);
    draw_content();
    if(m_current_menu)
    {
        t->draw_menu(*m_current_menu);
    }
    desktop::get().refresh();
}

void cogui::window::click(int x, int y)
{
    log_info() << "window click: x=" << x << " y=" << y << " sysmenu:" << m_sysmenu_btn_pos << " y=" << this->getY();

    //firstly: see if there is an open menu
    if(m_current_menu)
    {
        if(m_current_menu->inside(x, y))
        {
            auto tempm = m_current_menu;
            m_current_menu = nullptr;
            redraw();
            tempm->click(x, y);
        }
        else
        {
            // clicked outside the menu, close it
            m_current_menu->close();
            m_current_menu = nullptr;
            redraw();
        }
        return draw();
    }

    if(m_draw_state == draw_state::moving || m_draw_state == draw_state::resizing)
    {
        m_draw_state = draw_state::normal;
    }

    if(y == this->getY() && x == m_close_btn_pos)
    {
        // close click:
        // debug() << "click on close button";
        emit sig_on_close(this);
        return;
    }

    if(y == this->getY() && x == m_maximize_btn_pos)
    {
        // close click:
        // debug() << "click on close button";
        maximize();
        return;
    }

    // click on sysmenu?
    if(y == this->getY() && x == m_sysmenu_btn_pos)
    {
        log_info() << "click on sysmenu";
        m_current_menu = &m_sysmenu;
        m_current_menu->open(x - 1, y + 1);
        return draw();
    }

    // click on a menu from menubar
    if(hasMenubar())
    {
        for(auto& [m, p] : m_menu_positions)
        {
            log_info() << "Trying menu:" << m->caption() << "at (" <<p.first.first<<","<<p.first.second << ") - (" <<p.second.first<<","<<p.second.second << ") has (" << x << "," << y << ")";
            if(p.first.first <=x && p.second.first >= x && p.first.second <= y && p.second.second >= y)
            {
                log_info() << "Found click:" << m->caption();
                m_current_menu = m;
                m_current_menu->open(p.first.first, p.second.second + 1);
                return draw();
            }
        }
    }

    // did we click on a control by any chance?
    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        release_control(under);
        // debug() << "found under ontrol";
        under->click();
    }
    redraw();

}

void cogui::window::mouse_move(int x, int y)
{
    if(m_draw_state == draw_state::moving)
    {
        log_debug() << "mouse moving at" <<x<<","<<y;

        int new_x = x - m_mouse_down_x;
        int new_y = y - m_mouse_down_y;

        if(new_x >= 0 && new_y >= 0 && new_x + this->getWidth() < desktop::get().getWidth() - 1 && new_y + this->getHeight() < desktop::get().getHeight())
        {
            // debug() << "window moving at" <<x<<", "<<y;
            clear(); // clear is usually followed by a draw that why there is no refresh
            setX(new_x);
            setY(new_y);

            update_container();

            redraw();
        }
        else
        {
            // debug() << "window not moving at all at " <<x<<", "<<y;
        }
    }
    else
    if(m_draw_state == draw_state::resizing)
    {
        log_debug() << "mouse resizing at" <<x<<","<<y;

        int dx = x - m_mouse_down_x - this->getX();
        int dy = y - m_mouse_down_y - this->getY();

        int attempted_new_width = m_prev_w + dx;
        if(attempted_new_width <= minimumDrawableWidth())
        {
            return;
        }

        if(getWidth() +  dx >= 5 && getHeight() + dy >= 5)
        {
            clear(); // clear is usually followed by a draw that why there is no refresh
            // log_info() << "w = " << getWidth() << " nw=" << getWidth() + dx;

            int temptative_width = m_prev_w + dx;
            int temptative_height = m_prev_h + dy;

            if(m_layout)
            {
                if(!m_layout->accept_new_size(m_tab_order, temptative_width, temptative_height))
                {
                    // return only if the new layout size is smaller than the current size
                    if(temptative_width < getWidth() && temptative_height < getHeight())
                    {
                        redraw();
                    }
                }
            }

            setWidth( m_prev_w + dx);
            setHeight( m_prev_h + dy);

            // if there is a layout attached
            reLayout(getWidth(), getHeight(), true);

            emit sig_on_resize(this, m_prev_w + dx, m_prev_h + dy);

            redraw();
        }
    }
    else
    {
        // do we have an opened menu? That takes priority over controls
        if(m_current_menu)
        {
            log_debug() << "opened menu at" <<x<<","<<y;

            if(m_current_menu->inside(x, y))
            {
                log_debug() << "opened menu handles at" <<x<<","<<y;

                if(m_current_menu->mouse_move(x, y))
                {
                    log_debug() << "opened menu handled at" <<x<<","<<y << ", redrawing";

                    return draw();
                }
            }
            // do we have a menubar, if yes see if we are moving on in and open/close accordingly
            if(hasMenubar() && m_current_menu != &m_sysmenu)
            {
                for(auto& [m, p] : m_menu_positions)
                {
//                    log_info() << "Trying move menu:" << m->caption() << "at (" <<p.first.first<<","<<p.first.second << ") - (" <<p.second.first<<","<<p.second.second << ") has (" << x << "," << y << ")";
                    if(p.first.first <=x && p.second.first > x && p.first.second <= y && p.second.second >= y && m!=m_current_menu)
                    {
//                        log_info() << "Found move:" << m->caption();
                        m_current_menu->close();
                        m_current_menu = m;
                        m_current_menu->open(p.first.first, p.second.second + 1);
                        return redraw();
                    }
                }
            }
            return;
        }
        // now go to the controls, see if the mouse is over of one of them or not
        std::shared_ptr<control> under = element_under(x, y);
        if(under)
        {

            log_debug ()<< "got under element: " << under->getTitle();

            if(m_prev_pressed != m_tab_order.end() && !m_tab_order.empty())
            {
                if(under == *m_prev_pressed)
                {
                    m_pressed = m_prev_pressed;
                    (*m_pressed)->press();
//                    log_debug ()<< "got under element: " << under->getTitle() << "pressing and redrawing";

                    return draw();
                }

            }
            else
            {
//                log_debug ()<< "got under element: " << under->getTitle() << "focusing and redrawing";

                focus_element(under);
                return draw();
            }
        }

        // here we do not have an element under the cursor, however if we had one
        // make sure to un-press it
        if(m_pressed != m_tab_order.end() && !m_tab_order.empty())
        {
            m_prev_pressed = m_pressed;

            (*m_pressed)->release();
            (*m_pressed)->unfocus();

            m_pressed = m_tab_order.end();
            m_focused = m_tab_order.end();

//            log_debug ()<< "NO under element, but pressed != tab_order.end : " << (*m_prev_pressed)->getTitle() << "and redrawing";

            return draw();
        }
    }

    // now if there was a control we have focused on, unfocus it since we moved outside of it
    if(m_focused != m_tab_order.end() && !m_tab_order.empty())
    {
//        log_debug ()<< "NO under element, but focused != tab_order.end : " << (*m_focused)->getTitle() << "and redrawing";
        (*m_focused)->unfocus();
        m_focused = m_tab_order.end();
        return draw();
    }
}

bool cogui::window::inside(int x, int y) const
{
    return x >= this->getX()
            && x <= this->getX() + getWidth() + 1
            && y >= this->getY()
            && y <= this->getY() + getHeight()
            ;
}

void cogui::window::click()
{
    log_info() << "This window was clicked:" << this;
}

int cogui::window::minimumDrawableWidth() const
{
    return desktop::get().getTheme()->minimum_window_width(*this);
}

int cogui::window::minimumDrawableHeight() const
{
    return desktop::get().getTheme()->minimum_window_height(*this);
}

void cogui::window::redraw()
{
    desktop::get().redraw();
}

int cogui::window::first_available_row() const
{
    return desktop::get().getTheme()->first_available_row(*this);
}

void cogui::window::update_titlebar_btn_positions(int close_pos, int sysmenu_pos, int maximize_pos) const
{
    m_close_btn_pos = close_pos;
    m_sysmenu_btn_pos = sysmenu_pos;
    m_maximize_btn_pos = maximize_pos;
}

void cogui::window::update_menubar_positions(menu * m, std::pair<int, int> ul, std::pair<int, int> lr)
{
    m_menu_positions[m] = {ul, lr};
}

cogui::menu &cogui::window::getSystemMenu()
{
    return m_sysmenu;
}

const cogui::menu &cogui::window::getSystemMenu() const
{
    return m_sysmenu;
}

void cogui::window::closeCurrentMenu()
{
    m_current_menu->close();
    m_current_menu = nullptr;
}

void cogui::window::close()
{
    emit sig_on_close(this);
    desktop::get().remove_window(this);
}

cogui::menubar &cogui::window::get_main_menu()
{
    return m_mainmenu;
}

const cogui::scrollbar &cogui::window::get_scrollbar() const
{
    return m_scrollbar;
}

void cogui::window::register_menubar_hotkeys()
{
    auto& items = m_mainmenu.items();
    for(size_t i = 0; i < items.size(); i++)
    {
        menu& itm = const_cast<cogui::menu&>(items[i]);
        std::wstring caption = itm.caption();
        auto andp = caption.find(L"&");
        if(andp != std::string::npos && andp < caption.length() - 1)
        {
            std::wstring keydata;
            keydata += (wchar_t)caption[andp + 1];
            log_info() << "Hotkey found for" << caption << "as:" << keydata;
            cogui::events::keypress* hk = new cogui::events::keypress(cogui::events::key_class::key_textinput, true, false, false, keydata);
            std::shared_ptr<cogui::events::keypress> sp;
            sp.reset(hk);
            sp->set_as_hotkey();
            m_menubar_openers[sp] = &items[i];
        }
    }
}

bool cogui::window::activate_previous_menu()
{
    return activate_menu(std::bind(&menubar::before, &m_mainmenu, std::placeholders::_1));
}

bool cogui::window::activate_next_menu()
{
    return activate_menu(std::bind(&menubar::after, &m_mainmenu, std::placeholders::_1));
}

void cogui::window::left_mouse_down(int x, int y)
{
    log_debug() << "MOUSE DOWN: y=" << y << " topy=" << this->getY();

    if(deal_with_scrollbar_mouse_down(x, y))
    {
        return;
    }

    if( y == this->getY() && x != m_close_btn_pos && x != m_sysmenu_btn_pos) // down on the top line, usually this means move the window
    {
        if(m_current_menu)
        {
            m_current_menu = nullptr;
            redraw(); // this redraws the desktop since the menu might have covered some other window
        }

        // see: outside of sysmenu, maximize, close
        m_draw_state = draw_state::moving;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        return draw();
    }

    if(x == getWidth() + 1 + this->getX() && y == getHeight() + this->getY()) // in the lower right corner
    {
        if(m_current_menu)
        {
            m_current_menu = nullptr;
            redraw();
        }

        m_draw_state = draw_state::resizing;
        m_mouse_down_x = x - this->getX();
        m_mouse_down_y = y - this->getY();
        m_prev_w = getWidth();
        m_prev_h = getHeight();

        return draw();
    }

    // see if we have pressed the mouse on a control
    std::shared_ptr<control> under = element_under(x, y);
    if(under && !m_current_menu)
    {
        press_element(under);
        return draw();
    }

    // now if there was a control we have pressed the button on, release it since we clicked outside of it
    if(!m_tab_order.empty() && (m_prev_pressed != m_tab_order.end() || m_pressed != m_tab_order.end()) )
    {
        auto to_unpress_it = m_prev_pressed != m_tab_order.end() ? m_prev_pressed : m_pressed;
        release_control(*to_unpress_it);
        return draw();
    }

    // noone else captured this event, emit as a generic signal
    emit sig_on_mouse_down(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();
}

void cogui::window::left_mouse_up(int x, int y)
{
    log_debug() << "MOUSE UP: " << x << " " << y;
    m_draw_state = draw_state::normal;

    // now release the element if there was any pressed
    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        // see if the release has happened on the same control that was pressed on
        if(*m_prev_pressed == under)
        {
            release_control(under);
            // call the click
            under->click();
        }
        return draw();
    }

    // now if there was a control we have pressed the button on, release it
    if( !m_tab_order.empty() && (m_prev_pressed != m_tab_order.end() || m_pressed != m_tab_order.end()) )
    {
        auto to_unpress_it = m_prev_pressed != m_tab_order.end() ? m_prev_pressed : m_pressed;
        release_control(*to_unpress_it);
        return draw();
    }

    // nothing captured the left up, emit as signal
    emit sig_on_mouse_up(this, cogui::mouse::button::left, x - this->getX(), y - this->getY());
    draw();

}

void cogui::window::right_mouse_down(int x, int y)
{
    emit sig_on_mouse_down(this, cogui::mouse::button::right, x - this->getX(), y - this->getY());
}

void cogui::window::right_mouse_up(int x, int y)
{
    emit sig_on_mouse_up(this, cogui::mouse::button::right, x - this->getX(), y - this->getY());
}

void cogui::window::doubleclick(int x, int y)
{
    if(y == this->getY() && x != m_close_btn_pos && x != m_sysmenu_btn_pos) // down on the top line, usually this means move the window
    {
        maximize();
        return;
    }

    std::shared_ptr<control> under = element_under(x, y);
    if(under)
    {
        under->doubleclick(x,y);
    }
}


bool cogui::window::keypress(std::shared_ptr<cogui::events::keypress> k)
{
    log_debug() << "Key:" << k->get_chardata();

    // first try: was it a hotkey to open a menu?
    for(auto& [hk, m] : m_menubar_openers)
    {
        if(*hk == *k)
        {
            if(m_menu_positions.count(m))
            {
                m_current_menu = nullptr;
                redraw();

                auto p = m_menu_positions[m];
                m_current_menu = m;
                m_current_menu->open(p.first.first, p.second.second + 1);
                m_current_menu->activate_action(0);
                draw();
                return true;
            }
        }
    }

    // second try: if we do have an open menu let's see if we pressed a button which is in the menu itself and activate it
    if(m_current_menu)
    {
        // this will handle hotkeys for the menu and up/down
        if(m_current_menu->keypress(k))
        {
            draw();
            return true;
        }

        // let's see if this is right/left, if yes deactivate the current menu and activate the next/previous one
        // if handled, they will also redraw the screen
        if(*k == cogui::events::key_class::key_left)
        {
            if(activate_previous_menu())
            {
                return true;
            }
        }
        if(*k == cogui::events::key_class::key_right)
        {
            if(activate_next_menu())
            {
                return true;
            }
        }

        // if we press Esc, we should this close the open menu
        if(*k == cogui::events::key_class::key_escape)
        {
            m_current_menu = nullptr;
            redraw(); // this redraws the desktop since the menu might have covered some other window
            return true;
        }

        // if we press Enter/Return we should activate the currently selected action
        if(*k == cogui::events::key_class::key_return || *k == cogui::events::key_class::key_kp_enter)
        {

        }
    }

    // see if this was one of the hotkeys that were registered
    for(const auto& hkh : m_hotkeys)
    {
        log_debug() << "K=" << k->get_chardata() << " H:" << hkh->k->generator().get_chardata();

        if(*k == hkh->k->generator())
        {
            hkh->handle();
            return true;
        }
    }

    // emit it as a signal, since noone took it over

    std::shared_ptr<cogui::key> keys = std::make_shared<cogui::key>(*k);

    emit sig_on_keypress(this, keys);

    return false;
}

bool cogui::window::hasSysmenuButton() const
{
    return m_hasSysmenuButton;
}

void cogui::window::setHasSysmenuButton(bool hasSysmenuButton)
{
    m_hasSysmenuButton = hasSysmenuButton;
}

cogui::window::draw_state cogui::window::getDrawState() const
{
    return m_draw_state;
}

void cogui::window::maximize()
{

    if(m_window_state == window_state::normal)
    {
        m_initial_x = getX();
        m_initial_y = getY();
        m_initial_width = getWidth();
        m_initial_height = getHeight();

        setX(0);
        setY(0);
        setWidth(desktop::get().getWidth() - 2);
        setHeight(desktop::get().getHeight() - 1);

        m_window_state = window_state::maximized;

        reLayout();
    }
    else
    {
        desktop::get().clear();

        setX(m_initial_x);
        setY(m_initial_y);
        setWidth(m_initial_width);
        setHeight(m_initial_height);

        m_window_state = window_state::normal;

        reLayout();
    }

    redraw();
}

bool cogui::window::hasMaximizeButton() const
{
    return m_hasMaximizeButton;
}

void cogui::window::setHasMaximizeButton(bool hasMaximizeButton)
{
    m_hasMaximizeButton = hasMaximizeButton;
}

bool cogui::window::hasCloseButton() const
{
    return m_hasCloseButton;
}

void cogui::window::setHasCloseButton(bool hasCloseButton)
{
    m_hasCloseButton = hasCloseButton;
}

bool cogui::window::resizeable() const
{
    return m_resizeable;
}

void cogui::window::setResizeable(bool resizeable)
{
    m_resizeable = resizeable;
}
