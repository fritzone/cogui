#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include "theme.h"
#include "themes.h"

#include "dynamic_library.h"

#include <memory>

namespace cogui {

class theme_manager final
{
public:
    static theme_manager& instance();
    std::shared_ptr<theme> current_theme();
    std::shared_ptr<theme> get_theme(const std::string& theme_name);

private:

    theme_manager();

private:

    std::vector<std::pair<std::shared_ptr<dynamic_lib>, std::shared_ptr<theme>>> themes;
};

}

#endif // THEME_MANAGER_H
