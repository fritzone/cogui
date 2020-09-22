#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

#include <string>

namespace cogui
{
typedef void* dynamic_lib_handle;

struct dynamic_lib final
{
    dynamic_lib(const std::string &p);
    ~dynamic_lib();

    std::string	path;
    cogui::dynamic_lib_handle handle;
};

}

#endif // DYNAMIC_LIBRARY_H
