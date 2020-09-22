#include "graphics_engine_manager.h"
#include "graphics_engine.h"
#include <log.h>

cogui::graphics_engine_manager &cogui::graphics_engine_manager::instance()
{
    static graphics_engine_manager i;
    return i;
}

std::shared_ptr<cogui::graphics_engine> cogui::graphics_engine_manager::current_engine()
{
    log_info() << "Creating new curses";

    return std::shared_ptr<cogui::graphics_engine> (new ncurses);
}

std::shared_ptr<cogui::graphics_engine> cogui::graphics_engine_manager::get_engine(const std::string &n)
{
    return nullptr;
}
