#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include "theme.h"
#include "themes.h"

#include <memory>

namespace cogui {

class theme_manager
{
public:
    static theme_manager& instance();

    std::shared_ptr<theme> current_theme();

private:
    theme_manager();
    std::vector<std::shared_ptr<theme>> themes;

};

}

#endif // THEME_MANAGER_H
