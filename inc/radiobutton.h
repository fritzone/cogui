#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "control.h"
#include "miso.h"
#include "desktop.h"
#include "theme.h"
#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "themeable.h"
#include "clickable.h"
#include "state_changer.h"
#include "checkable.h"
#include "control_creator.h"
#include "string_type.h"

namespace cogui {

class radiobutton : public themeable<radiobutton>, public checkable<radiobutton>, public control_creator<radiobutton>
{
public:

    template<StringType S, typename ... Args>
    radiobutton(int x, int y, int width, int height, const S& title, Args... args) :
        themeable(x, y, width, height, title, this, builtin_radiobutton_draw, builtin_radiobutton_minimum_radiobutton_width, builtin_radiobutton_minimum_radiobutton_height),
        checkable<radiobutton>(this)
    {
        if constexpr (sizeof... (args))
        {
            init(overload_unref(clickable<radiobutton>::connector(this),
                                state_changer<radiobutton,bool>::connector(this),
                                checkable<radiobutton>::connector(this)),
                 std::forward<Args>(args)...);
        }
    }

    void click(int x, int y) override;

    template<StringType S, typename ... Args>
    radiobutton(const S& title, Args... args) :
        radiobutton(-1, -1, 0, 0, title, std::forward<Args>(args)...)
    {}
};

}

#endif // RADIOBUTTON_H
