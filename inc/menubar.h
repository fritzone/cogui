#ifndef MENUBAR_H
#define MENUBAR_H

#include "menu.h"

#include <initializer_list>

namespace cogui {

/**
 * @brief The menubar class repesents the menubar of a window
 */
class menubar
{
public:
    menubar() = default;
    menubar(const menubar&) = default;

    bool operator == (const menubar& oth) const ;

    menubar(std::initializer_list<menu> entries);

    menubar& operator = (std::initializer_list<menu> m);

    const menu& operator[](int i) const;
    const std::vector<menu>& items() const;
    std::vector<menu>& items();

    static menubar no_mainmenu;
    static cogui::menu align_right_after;

    // returns the menu before the menu in the parameter
    menu* before(menu*);
    // returns the menu after the menu in the parameter
    menu* after(menu*);

private:
    std::vector<menu> m_menus;

};

}

#endif // MENUBAR_H
