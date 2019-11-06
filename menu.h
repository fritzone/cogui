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
        template<typename ... Args>
        action(const std::wstring& title, Args... args) : m_title(title)
        {
            auto connector = overload_unref(
                [&,this](OnTrigger c) { miso::connect(this, sig_on_trigger, c.get()); }
            );

            auto tup = std::make_tuple(std::forward<Args>(args)...);

            for (auto const& elem : to_range(tup))
            {
                std::visit(connector, elem);
            }
        }

        using OnTrigger = fluent::NamedType<std::function<void(action*)>, struct OnTriggerHelper>;
        static OnTrigger::argument on_trigger;

        miso::signal<action*> sig_on_trigger;
        std::wstring getTitle() const;
        void setTitle(const std::wstring &getTitle);

    private:
        std::wstring m_title;
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

        const action& operator[](int i) const;

    private:
        std::vector<action> m_actions;
        int m_x = 0;
        int m_y = 0;
        int m_width = 0;
        int m_height = 0;
    };

}

#endif // MENU_H
