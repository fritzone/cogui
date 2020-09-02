#ifndef COGUI_H
#define COGUI_H

#include "application.h"
#include "window.h"
#include "button.h"
#include "menu.h"
#include "arguments.h"

namespace cogui {

class textflags
{
public:
    enum value : uint64_t
    {
        v_normal = 0,
        v_bold = 1 << 9,
        v_underline = 1 << 13
    };

    static textflags normal;
    static textflags bold;
    static textflags underline;

    textflags() = default;

    textflags(value a) : m_value(a) { }
    textflags(int a) : m_value(a) { }

    int operator &(const textflags& o) const;

    operator int() const;

private:
    int m_value;


};

}

#endif // COGUI_H
