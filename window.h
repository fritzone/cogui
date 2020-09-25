#ifndef WINDOW_H
#define WINDOW_H

#include "container.h"
#include "miso.h"
#include "desktop.h"
#include "mouse.h"
#include "menu.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

#include <string>
#include <tuple>
#include <functional>

namespace cogui
{

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
        init();
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
    void doubleclick(int x, int y);

    /* keyboard press event */
    bool keypress(std::shared_ptr<cogui::events::key> k);

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

    void update_titlebar_btn_positions(int close_pos, int sysmenu_pos, int maximize_pos) const;
    void update_menubar_positions(menu*, std::pair<int, int>, std::pair<int, int>);

    menu &getSystemMenu();
    const menu &getSystemMenu() const;
    void closeCurrentMenu();

    // returns the main menubar of this window
    bool hasMenubar() const
    {
        bool b = (&m_mainmenu == &cogui::menubar::no_mainmenu);
        return !b;
    }
    menubar &getMainMenu();

    // signals

    using OnResize = fluent::NamedType<std::function<void(window*,int,int)>, struct OnResizeHelper>;
    using OnMouseDown = fluent::NamedType<std::function<void(window*,mouse::button,int,int)>, struct OnMouseDownHelper>;
    using OnMouseUp = fluent::NamedType<std::function<void(window*,mouse::button,int,int)>, struct OnMouseUpHelper>;
    using OnClose = fluent::NamedType<std::function<void(window*)>, struct OnCloseHelper>;

    static OnResize::argument on_resize;
    static OnClose::argument on_close;
    static OnMouseDown::argument on_mouse_down;
    static OnMouseUp::argument on_mouse_up;

    miso::signal<window*, int, int> sig_on_resize {"on_resize"};
    miso::signal<window*> sig_on_close {"on_close"};
    miso::signal<window*,mouse::button,int,int> sig_on_mouse_down {"mouse_down"};
    miso::signal<window*,mouse::button,int,int> sig_on_mouse_up {"mouse_up"};

    // system menu
    using SystemMenu = fluent::NamedType<menu, struct SystemMenuHelper>;
    static SystemMenu::argument sysmenu;

    // menubar
    using MenuBar = fluent::NamedType<menubar, struct MenuBarHelper>;
    static MenuBar::argument mainmenu;
private:

    menu m_sysmenu;
    menubar m_mainmenu = cogui::menubar::no_mainmenu;

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
    std::map<std::shared_ptr<cogui::events::key>, menu*> m_menubar_openers;

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
            [&,this](OnMouseDown m) { miso::connect(this, sig_on_mouse_down, m.get()); },
            [&,this](OnMouseUp m) { miso::connect(this, sig_on_mouse_up, m.get()); },
            [&,this](SystemMenu m) {m_sysmenu = m.get(); m_hasSysmenuButton = true; },
            [&,this](MenuBar m) {m_mainmenu = m.get(); }
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
    }

private:

    void register_menubar_hotkeys();
};

}

#endif // WINDOW_H
