#ifndef MENU_H
#define MENU_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

#include <initializer_list>
#include <string>

namespace cogui
{
    class action
    {
        using Selectable = bool;

    public:

        action() = default;
        action(action&&) = default;

        virtual ~action();
        action(const action& o);

        action& operator=(const action& o);
        action& operator=(action&& o) = default;

        action(const std::wstring& title) : m_title(title)
        {
        }

        template<typename ... Args>
        action(const std::wstring& title, Args... args) : m_title(title)
        {
            resolve_named_parameters(std::forward<Args>(args)...);
        }
        template<typename ... Args>
        action(const std::wstring& title, Selectable s, Args... args) : m_title(title), m_selectable(true)
        {
            resolve_named_parameters(std::forward<Args>(args)...);
        }

        template<typename ... Args>
        void resolve_named_parameters(Args... args)
        {
            auto connector = overload_unref(
                [&,this](OnTrigger c) { m_conn = c; miso::connect(this, sig_on_trigger, c.get()); }
            );

            auto tup = std::make_tuple(std::forward<Args>(args)...);

            for (auto const& elem : to_range(tup))
            {
                std::visit(connector, elem);
            }
        }

        void trigger();
        std::wstring getTitle() const;
        void setTitle(const std::wstring &getTitle);

        // triggering signal
        using OnTrigger = fluent::NamedType<std::function<void(action*)>, struct OnTriggerHelper>;
        static OnTrigger::argument on_trigger;
        miso::signal<action*> sig_on_trigger {"on_trigger"};

        // whether it is selectable or not
        static Selectable selectable;

        bool isSelectable() const;

    private:
        std::wstring m_title;
        OnTrigger m_conn;
        bool m_selectable = false;
        bool m_selected = false;
    };

    /**
     * @brief The menu class is responsible for representing one menu either in the form of a sysmenu,
     * or in the form of a popup menu, or as part of a menubar
     */
    class menu
    {
    public:
        menu() = default;
        menu(std::initializer_list<action> l);
        menu(const std::wstring& caption, std::initializer_list<action> l);
        menu(const wchar_t * const caption, std::initializer_list<action> l);
        menu(const std::string& caption, std::initializer_list<action> l);

        void append(std::initializer_list<action> l);

        menu& operator =(std::initializer_list<action> l);

        bool operator == (const menu& rhs) const;

        // calculates the positions and opens the menu
        void open(int x, int y);

        void close();

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;

        bool inside(int x, int y) const;
        bool mouse_move(int x, int y);
        bool click(int x, int y);

        bool isOpened() const;

        const action& operator[](int i) const;

        int getLastSelectedIndex() const;
        bool isSysmenu() const;
        std::wstring caption() const;

        static cogui::action separator_item;

    private:
        std::vector<action> m_actions;
        int m_x = 0;
        int m_y = 0;
        int m_width = 0;
        int m_height = 0;
        int m_lastSelectedIndex = -1;
        bool m_is_sysmenu = true;
        bool m_opened = false;
        std::wstring m_caption = L"";
    };

    /**
     * @brief The menubar class repesents the menubar of a window
     */
    class menubar
    {
    public:
        menubar() = default;
        menubar(std::initializer_list<menu> entries);

        menubar& operator = (std::initializer_list<menu> m);

        const menu& operator[](int i) const;
        const std::vector<menu>& items() const;

        static menubar no_mainmenu;
        static cogui::menu align_right_after;

    private:
        std::vector<menu> m_menus;

    };
}

#endif // MENU_H
