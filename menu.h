#ifndef MENU_H
#define MENU_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"
#include "events.h"
#include "action.h"

#include <initializer_list>
#include <string>
#include <map>
#include <memory>

namespace cogui
{

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

        bool keypress(std::shared_ptr<cogui::events::keypress> k);

        void activate_action(size_t index);
        void activate_next_action();
        void activate_previous_action();

        void trigger_action(size_t index);
        void trigger_current_action();

        bool isOpened() const;

        const action& operator[](int i) const;

        int getLastSelectedIndex() const;
        bool isSysmenu() const;
        std::wstring caption() const;

        static cogui::action separator_item;

        int get_action_count() const;

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
        std::map<std::shared_ptr<cogui::events::keypress>, action*> m_action_activators;

    private:

        void register_action_activators();


    };

}

#endif // MENU_H
