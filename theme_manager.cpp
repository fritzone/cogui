#include "theme_manager.h"

#include <dlfcn.h>
#include <filesystem>
namespace fs = std::filesystem;

typedef void* dynamic_lib_handle;
static dynamic_lib_handle load_lib(const std::string& path);
static cogui::theme* instantiate(const dynamic_lib_handle handle);
static void close_lib(dynamic_lib_handle handle);

struct dynamic_lib {
    std::string			path;
    dynamic_lib_handle  handle;

    dynamic_lib(std::string p) : path(p), handle(nullptr) {}
};

cogui::theme_manager &cogui::theme_manager::instance()
{
    static theme_manager i;
    return i;
}

std::shared_ptr<cogui::theme> cogui::theme_manager::current_theme()
{
    if(!themes.empty())
    {
        return themes[0];
    }
    else
    {
        log_warning() << "There are no themes created, the application will crash";
        return nullptr;
    }
}

cogui::theme_manager::theme_manager()
{
    std::string path = "/usr/local/lib/cogui/themes";
    std::vector<dynamic_lib> libs;
    for (const auto & entry : fs::directory_iterator(path))
    {
        log_info() << "Using theme library:" << entry.path();
        libs.push_back(dynamic_lib(entry.path()));
    }
    for (auto& l : libs)
    {
        l.handle = load_lib(l.path);
    }


    // instantiate!
    for (auto& l : libs)
    {
        auto lib = instantiate(l.handle);
        std::shared_ptr<theme> spl = std::shared_ptr<theme>(lib);
        log_info() << "Created theme:" << spl->name();
        themes.push_back( spl );
    }

}

static dynamic_lib_handle load_lib(const std::string& path) {
    std::cout << "Trying to open: " << path << std::endl;
    return dlopen(path.data() , RTLD_NOW); // get a handle to the lib, may be nullptr.
            // RTLD_NOW ensures that all the symbols are resolved immediately. This means that
            // if a symbol cannot be found, the program will crash now instead of later.
}

static void close_lib(dynamic_lib_handle handle) {
    dlclose(handle);
}

static cogui::theme* instantiate(const dynamic_lib_handle handle) {

    if (handle == nullptr) return nullptr;

    void *maker = dlsym(handle , "create");

    if (maker == nullptr) return nullptr;

    typedef cogui::theme * (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}
