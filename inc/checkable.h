#ifndef CHECKABLE_H
#define CHECKABLE_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "state_changer.h"
#include "clickable.h"

namespace cogui
{

template <typename C>
struct checkable :  public clickable<C>, public state_changer<C, bool>
{
public:

    checkable(C* ctrl) : m_ctrl(ctrl), state_changer<C,bool>({false, true})
    {
    }

    // check state
    using CheckState = fluent::NamedType<bool, struct CheckStateHelper>;
    static CheckState::argument checked;

    void set_checked(bool c)
    {
        state_changer<C,bool>::set_state(m_ctrl, c);
        m_ctrl->redraw();
    }

    bool is_checked() const
    {
        return state_changer<C,bool>::get_state();

    }
    void check()
    {
        state_changer<C,bool>::set_state(m_ctrl, true);
        m_ctrl->redraw();
    }

    void uncheck()
    {
        state_changer<C,bool>::set_state(m_ctrl, false);
        m_ctrl->redraw();
    }

    void click(C* ctrl)
    {
        state_changer<C,bool>::set_next_state();
        state_changer<C,bool>::set_state(ctrl, state_changer<C,bool>::get_state());
        clickable<C>::click(ctrl);
        m_ctrl->redraw();
    }

    auto connector(C* ctrl)
    {
        return [&,ctrl](CheckState cs) {state_changer<C,bool>::set_state(cs.get()); };
    }


    C* m_ctrl ;
};

}

template<typename C>
typename cogui::checkable<C>::CheckState::argument cogui::checkable<C>::checked;

#endif // CHECKABLE_H
