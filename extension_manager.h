#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include "theme.h"
#include "themes.h"
#include "graphics_engine.h"
#include "graphic_engines.h"

#include "dynamic_library.h"

#include <memory>
#include <filesystem>
namespace fs = std::filesystem;

namespace cogui {

template<class T>
T* instantiate(const cogui::dynamic_lib_handle handle)
{
    if (handle == nullptr)
    {
        log_error() << "Trying to instantiate a NULL handle";
        return nullptr;
    }

    void *maker = load_function(handle , "create");

    if (maker == nullptr)
    {
        log_error() << "Can't load maker function";

        return nullptr;
    }

    typedef T * (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}


template<typename T>
class extension_manager final
{
public:
    static extension_manager<T>& instance()
    {
        static extension_manager<T> i;
        return i;
    }

    std::shared_ptr<T> current_loadable()
    {
        if(!m_loadables.empty())
        {
            return m_loadables[0].second;
        }
        else
        {
            log_warning() << "There are no loadables created for " << T::type<< ", the application might crash";
            return nullptr;
        }
    }

    std::shared_ptr<T> get_loadable(const std::string& name)
    {
        for(const auto& [lib, l] : m_loadables)
        {
            if(l->name() == name)
            {
                return l;
            }
        }
        return current_loadable();
    }
private:
    extension_manager()
    {
        std::string path = T::path; // "/usr/local/lib/cogui/themes";

        // instantiate!
        for (const auto & entry : fs::directory_iterator(path))
        {
            std::shared_ptr<dynamic_lib> l = std::make_shared<dynamic_lib>(entry.path());
            m_loadables.emplace_back(l, std::shared_ptr<T>(cogui::instantiate<T>(l->handle)));
        }
    }
private:
    std::vector<std::pair<std::shared_ptr<dynamic_lib>, std::shared_ptr<T>>> m_loadables;

};

using theme_manager = extension_manager<cogui::theme>;
using graphics_engine_manager = extension_manager<cogui::graphics_engine>;

}

#endif // THEME_MANAGER_H
