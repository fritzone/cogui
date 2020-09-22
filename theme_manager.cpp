#include "theme_manager.h"

#include <dlfcn.h>
#include <filesystem>
namespace fs = std::filesystem;

static cogui::dynamic_lib_handle load_lib(const std::string& path);
static cogui::theme* instantiate(const cogui::dynamic_lib_handle handle);
static void close_lib(cogui::dynamic_lib_handle handle);


cogui::theme_manager &cogui::theme_manager::instance()
{
    static theme_manager i;
    return i;
}

std::shared_ptr<cogui::theme> cogui::theme_manager::current_theme()
{
    if(!themes.empty())
    {
        return themes[0].second;
    }
    else
    {
        log_warning() << "There are no themes created, the application will crash";
        return nullptr;
    }
}

std::shared_ptr<cogui::theme> cogui::theme_manager::get_theme(const std::string &theme_name)
{
    for(const auto& [lib, theme] : themes)
    {
        if(theme->name() == theme_name)
        {
            return theme;
        }
    }
    return current_theme();
}

cogui::theme_manager::theme_manager()
{
    std::string path = "/usr/local/lib/cogui/themes";

    // instantiate!
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::shared_ptr<dynamic_lib> l = std::make_shared<dynamic_lib>(entry.path());
        themes.emplace_back(l, std::shared_ptr<theme>(instantiate(l->handle)));
    }

}

static cogui::dynamic_lib_handle load_lib(const std::string& path)
{
    cogui::dynamic_lib_handle h = dlopen(path.data() , RTLD_NOW);
    if(!h)
    {
        log_error() << "Could not load:" << path;
    }

    return h;
}

static void close_lib(cogui::dynamic_lib_handle handle)
{
    log_info() << "Cleaning up";
    dlclose(handle);
}

static cogui::theme* instantiate(const cogui::dynamic_lib_handle handle)
{
    if (handle == nullptr)
    {
        log_error() << "Trying to instantiate a NULL handle";
        return nullptr;
    }

    void *maker = dlsym(handle , "create");

    if (maker == nullptr)
    {
        log_error() << "Can't load maker function";

        return nullptr;
    }

    typedef cogui::theme * (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}

cogui::dynamic_lib::dynamic_lib(const std::string& p) : path(p), handle(nullptr)
{
    handle = load_lib(p);
}

cogui::dynamic_lib::~dynamic_lib()
{
    log_info() << "destroyed:" << path;
    close_lib(handle);
}

