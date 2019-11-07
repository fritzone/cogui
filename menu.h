#ifndef MENU_H
#define MENU_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

#include <initializer_list>
#include<vector>

namespace cogui
{
    class action
    {
    public:

        action() = default;
        virtual ~action();
        action(const action& o);

        action& operator=(const action& o);

        template<typename ... Args>
        action(const std::wstring& title, Args... args) : m_title(title)
        {
            auto connector = overload_unref(
                [&,this](OnTrigger c) { conn = c; miso::connect(this, sig_on_trigger, c.get()); }
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

    private:
        std::wstring m_title;
        OnTrigger conn;

    };

    class menu
    {
    public:
        menu() = default;
        menu(std::initializer_list<action> l);

        void append(std::initializer_list<action> l);

        menu& operator =(std::initializer_list<action> l);

        // calculates the positions and opens the menu
        void open(int x, int y);

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;

        bool inside(int x, int y) const;
        bool mouse_move(int x, int y);
        bool click(int x, int y);

        const action& operator[](int i) const;

        int getLastSelectedIndex() const;

    private:
        std::vector<action> m_actions;
        int m_x = 0;
        int m_y = 0;
        int m_width = 0;
        int m_height = 0;
        int m_lastSelectedIndex = -1;
    };

}

#endif // MENU_H
