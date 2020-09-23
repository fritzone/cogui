#include "dynamic_library.h"
#include <dlfcn.h>
#include <log.h>

cogui::dynamic_lib_handle cogui::load_lib(const std::string& path)
{
    cogui::dynamic_lib_handle h = dlopen(path.data() , RTLD_NOW);
    if(!h)
    {
        log_error() << "Could not load:" << path;
    }

    return h;
}

void cogui::close_lib(cogui::dynamic_lib_handle handle)
{
    log_info() << "Cleaning up";
    dlclose(handle);
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

cogui::function_address cogui::load_function(dynamic_lib_handle handle, const char* fun)
{
    void *maker = dlsym(handle , fun);
    if(!maker)
    {
        log_error() << "Could not load the requested function:" << fun;
    }
    return maker;
}
