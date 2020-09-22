#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <memory>
#include <string>

#include "graphic_engines.h"

namespace cogui
{
class graphics_engine;

class graphics_engine_manager final
{
public:
    static graphics_engine_manager& instance();

    std::shared_ptr<graphics_engine> current_engine();
    std::shared_ptr<graphics_engine> get_engine(const std::string& n);
};

}

#endif // ENGINE_MANAGER_H
