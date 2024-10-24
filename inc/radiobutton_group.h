#ifndef RADIOBUTTON_GROUP_H
#define RADIOBUTTON_GROUP_H

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
#include "radiobutton.h"
#include "utils.h"
#include "control_creator.h"
#include "control_grouper.h"

#include <numeric>

namespace cogui
{
class radiobutton_group : public themeable<radiobutton_group>, public state_changer<radiobutton_group, int>, public control_grouper<radiobutton>
{
public:

    template<typename S, typename ... Args>
    radiobutton_group(int x, int y, const S& title, const std::initializer_list<radiobutton::CREATOR>& buttons, Args... args) :
        themeable<radiobutton_group>(x, y, -1, -1, title, this, builtin_radiobutton_group_draw, builtin_radiobutton_group_minimum_radiobutton_group_width, builtin_radiobutton_group_minimum_radiobutton_group_height),
        state_changer<radiobutton_group, int>(cogui::utils::generate_sequence(buttons.size())),
        control_grouper<radiobutton>(buttons)
    {
        set_width(calculate_width());
        set_height(calculate_height());

        if constexpr (sizeof... (args))
        {
            init(overload_unref( state_changer<radiobutton_group, int>::connector(this)), std::forward<Args>(args)...);
        }
    }

    void click(int x, int y) override;

private:

    int m_selected_idx = -1;
};

}

#endif // RADIOBUTTON_GROUP_H
