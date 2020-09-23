#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

#include <string>

namespace cogui
{

typedef void* dynamic_lib_handle;
typedef void* function_address;

struct dynamic_lib final
{
    dynamic_lib(const std::string &p);
    ~dynamic_lib();

    std::string	path;
    cogui::dynamic_lib_handle handle;
};

cogui::dynamic_lib_handle load_lib(const std::string& path);
void close_lib(cogui::dynamic_lib_handle handle);
function_address load_function(dynamic_lib_handle l, const char* fun);

}

#endif // DYNAMIC_LIBRARY_H
