#ifndef WINDOW_H
#define WINDOW_H

#include "key.h"
#include "container.h"
#include "miso.h"
#include "desktop.h"
#include "mouse.h"
#include "menu.h"
#include "menubar.h"
#include "scrollbar.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

#include <string>
#include <tuple>
#include <functional>

namespace cogui
{

/**
 * @brief The window class represents a window component the user can place on the screen and interact with.
 *
 * Each application needs at least one window, that can hold several controls.
 */
class window : public container
{
public:

    // which state the window currently is in, used for drawing.
    enum class draw_state
    {
        normal,
        resizing,
        moving
    };

    // whether the window is in a normal state or maximized
    enum class window_state
    {
        normal,
        maximized
    };

    /**
     * Will create a window on the current screen.
     * @param x,y - the start position of the windows
     * @param w,h - the width and height of the windows
     */
    template<typename S>
    window(int x, int y, int width, int height, const S& title) : container(x, y, width, height, title)
    {
        desktop::get().add_window(this);
    }

    template<typename S, typename ... Args>
    window(int x, int y, int width, int height, const S& title, Args... args): container(x, y, width, height, title)
    {
        init(std::forward<Args>(args)...);
    }

    ~window() override;

    void draw() const override;

    /* mouse related */
    void click(int x, int y);
    void mouse_move(int x, int y);
    void left_mouse_down(int x, int y);
    void left_mouse_up(int x, int y);
    void right_mouse_down(int x, int y);
    void right_mouse_up(int x, int y);
    void doubleclick(int x, int y) override;

    /* keyboard press event */
    bool keypress(std::shared_ptr<cogui::events::keypress> k);

    bool resizeable() const;
    void setResizeable(bool resizeable);

    bool hasCloseButton() const;
    void setHasCloseButton(bool hasCloseButton);

    bool hasMaximizeButton() const;
    void setHasMaximizeButton(bool hasMaximizeButton);

    bool hasSysmenuButton() const;
    void setHasSysmenuButton(bool hasSysmenuButton);

    draw_state getDrawState() const;
    void maximize();

    bool inside(int x, int y) const override;
    void click() override;
    int minimumDrawableWidth() const override;
    int minimumDrawableHeight() const override;
    void redraw() override;
    int first_available_row() const override;

    void update_titlebar_btn_positions(int close_pos, int sysmenu_pos, int maximize_pos) const;
    void update_menubar_positions(menu*, std::pair<int, int>, std::pair<int, int>);

    menu &getSystemMenu();
    const menu &getSystemMenu() const;
    void closeCurrentMenu();

    void close();

    // returns the main menubar of this window
    bool hasMenubar() const
    {
        bool b = (m_mainmenu == cogui::menubar::no_mainmenu);
        return !b;
    }
    menubar &get_main_menu();
    const scrollbar& get_scrollbar() const;

    // signals
    using OnResize = fluent::NamedType<std::function<void(window*,int,int)>, struct OnResizeHelper>;
    using OnMouseDown = fluent::NamedType<std::function<void(window*,mouse::button,int,int)>, struct OnMouseDownHelper>;
    using OnMouseUp = fluent::NamedType<std::function<void(window*,mouse::button,int,int)>, struct OnMouseUpHelper>;
    using OnClose = fluent::NamedType<std::function<void(window*)>, struct OnCloseHelper>;
    using OnKeypress = fluent::NamedType<std::function<void(window*, std::shared_ptr<cogui::key>)>, struct OnKeypressHelper>;

    static OnResize::argument on_resize;
    static OnClose::argument on_close;
    static OnMouseDown::argument on_mouse_down;
    static OnMouseUp::argument on_mouse_up;
    static OnKeypress::argument on_keypress;

    miso::signal<window*, int, int> sig_on_resize {"on_resize"};
    miso::signal<window*> sig_on_close {"on_close"};
    miso::signal<window*,mouse::button,int,int> sig_on_mouse_down {"on_mouse_down"};
    miso::signal<window*,mouse::button,int,int> sig_on_mouse_up {"on_mouse_up"};
    miso::signal<window*,std::shared_ptr<cogui::key>> sig_on_keypress {"on_keypress"};
    
    // hotkey map
    using HotkeyT = fluent::NamedType<hotkey_associations, struct HotkeyHelper>;
    static HotkeyT::argument hotkeys;

    // system menu
    using SystemMenu = fluent::NamedType<menu, struct SystemMenuHelper>;
    static SystemMenu::argument sysmenu;

    // menubar
    using MenuBar = fluent::NamedType<menubar, struct MenuBarHelper>;
    static MenuBar::argument mainmenu;

    // scrollbar
    using ScrollBar = fluent::NamedType<scrollbar, struct ScrollBarHelper>;
    static ScrollBar::argument scrollbars;

private:

    menu m_sysmenu;
    menubar m_mainmenu = cogui::menubar::no_mainmenu;
    hotkey_associations m_hotkeys;
    scrollbar m_scrollbar;

    bool m_resizeable = true;
    bool m_hasCloseButton = true;
    bool m_hasMaximizeButton = true;
    bool m_hasSysmenuButton = false;

    draw_state m_draw_state = draw_state::normal;
    window_state m_window_state = window_state::normal;

    int m_mouse_down_x = -1;
    int m_mouse_down_y = -1;
    int m_prev_w = -1;
    int m_prev_h = -1;
    mutable int m_close_btn_pos = -1;
    mutable int m_sysmenu_btn_pos = -1;
    mutable int m_maximize_btn_pos = -1;

    // this is the current menu that is shown on the screen
    menu* m_current_menu = nullptr;

    // this will hold the positions where the menu was drawn
    // key is the menu, followed by two coordinates on the screen, upper left, lower right corner
    mutable std::map<menu*, std::pair<std::pair<int, int>, std::pair<int, int>>> m_menu_positions;

    // this will hold the hotkey and the associated menubar item
    std::map<std::shared_ptr<cogui::events::keypress>, menu*> m_menubar_openers;

private:

    template<typename ... Args>
    void init(Args... args)
    {
        desktop::get().add_window(this);
        resolve_named_parameters(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    void resolve_named_parameters(Args... args)
    {
        auto connector = overload_unref(
            [&,this](OnResize r) { miso::connect(this, sig_on_resize, r.get()); },
            [&,this](OnClose c) { miso::connect(this, sig_on_close, c.get()); },
            [&,this](OnKeypress k) { miso::connect(this, sig_on_keypress, k.get()); },
            [&,this](OnMouseDown m) { miso::connect(this, sig_on_mouse_down, m.get()); },
            [&,this](OnMouseUp m) { miso::connect(this, sig_on_mouse_up, m.get()); },
            [&,this](SystemMenu m) {m_sysmenu = m.get(); m_hasSysmenuButton = true; },
            [&,this](MenuBar m) {m_mainmenu = m.get(); },
            [&,this](HotkeyT h) {m_hotkeys = h.get(); },
            [&,this](ScrollBar s) {m_scrollbar = s.get(); }
        );

        auto tup = std::make_tuple(std::forward<Args>(args)...);

        for (auto const& elem : to_range(tup))
        {
            std::visit(connector, elem);
        }

        // see if we have mainmenu
        if(hasMenubar())
        {
            register_menubar_hotkeys();
        }

        // register the receiving window for the hotkeys
        for(auto& h : m_hotkeys)
        {
            h->set_window(this);
        }

        if(m_scrollbar.get_orientation() != scrollbar::orientation::so_none)
        {
            if(m_scrollbar.get_orientation() == scrollbar::orientation::so_both)
            {
                m_horizontal_scrollbar.reset(new scrollbar);
                m_horizontal_scrollbar->set_orientation(scrollbar::orientation::so_horizontal);
                m_horizontal_scrollbar->set_parent(this);
                m_vertical_scrollbar.reset(new scrollbar);
                m_vertical_scrollbar->set_orientation(scrollbar::orientation::so_vertical);
                m_vertical_scrollbar->set_parent(this);
            }
            else
            if(m_scrollbar.get_orientation() == scrollbar::orientation::so_vertical)
            {
                m_vertical_scrollbar.reset(new scrollbar);
                m_vertical_scrollbar->set_orientation(scrollbar::orientation::so_vertical);
                m_vertical_scrollbar->set_parent(this);
            }
            else
            if(m_scrollbar.get_orientation() == scrollbar::orientation::so_horizontal)
            {
                m_horizontal_scrollbar.reset(new scrollbar);
                m_horizontal_scrollbar->set_orientation(scrollbar::orientation::so_horizontal);
                m_horizontal_scrollbar->set_parent(this);
            }

        }
    }

    template<class T> bool activate_menu(T chooser)
    {
        if(m_current_menu)
        {
            auto m_prev_menu = m_current_menu;
            m_current_menu = nullptr;
            redraw(); // this redraws the desktop since the menu might have covered some other window
            m_current_menu = m_prev_menu;
        }

        m_current_menu = chooser(m_current_menu);
        if(m_menu_positions.count(m_current_menu))
        {
            auto p = m_menu_positions[m_current_menu];

            m_current_menu->open(p.first.first, p.second.second + 1);
            m_current_menu->activate_action(0);
            draw();
        }
        else
        {
            log_error() << "Lost a menu somewhere";
            return false;
        }

        return true;
    }

private:

    void register_menubar_hotkeys();
    bool activate_previous_menu();
    bool activate_next_menu();
};

}

#endif // WINDOW_H
