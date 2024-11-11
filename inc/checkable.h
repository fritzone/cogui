#ifndef CHECKABLE_H
#define CHECKABLE_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "state_changer.h"
#include "clickable.h"

namespace cogui
{
/**
 * @class checkable
 * @brief A template class that provides checkable functionality to a control.
 *
 * The `checkable` class extends the functionality of a control by making it checkable.
 * It provides methods to set, get, check, and uncheck the state of the control, as well as
 * a method to handle clicks. The state of the control is managed using the `state_changer` base class.
 *
 * @tparam C The type of the control to which checkable functionality is added.
 */
template <typename C>
class checkable : public clickable<C>, public state_changer<C, bool>
{
public:

    /**
     * @brief Constructs a checkable object.
     *
     * Initializes the control and sets the possible states to `false` and `true`.
     *
     * @param ctrl Pointer to the control to which checkable functionality is added.
     */
    checkable(C* ctrl) : m_ctrl(ctrl), state_changer<C,bool>({false, true})
    {
    }

    // connection to the outside world
    using CheckState = fluent::NamedType<bool, struct CheckStateHelper>;
    static CheckState::argument checked;

    /**
     * @brief Sets the checked state of the control.
     *
     * @param c The new checked state.
     */
    void set_checked(bool c)
    {
        state_changer<C,bool>::set_state(m_ctrl, c);
        m_ctrl->redraw();
    }

    /**
     * @brief Gets the current checked state of the control.
     *
     * @return The current checked state.
     */
    bool is_checked() const
    {
        return state_changer<C,bool>::get_state();
    }

    /**
     * @brief Sets the control to the checked state.
     */
    void check()
    {
        state_changer<C,bool>::set_state(m_ctrl, true);
        m_ctrl->redraw();
    }

    /**
     * @brief Sets the control to the unchecked state.
     */
    void uncheck()
    {
        state_changer<C,bool>::set_state(m_ctrl, false);
        m_ctrl->redraw();
    }

    /**
     * @brief Handles the click event for the control.
     *
     * Toggles the checked state and invokes the click action.
     *
     * @param ctrl Pointer to the control.
     */
    void click(C* ctrl)
    {
        state_changer<C,bool>::set_next_state();
        state_changer<C,bool>::set_state(ctrl, state_changer<C,bool>::get_state());
        clickable<C>::click(ctrl);
        m_ctrl->redraw();
    }

    /**
     * @brief Creates a connector function for the control.
     *
     * The connector function can be used to set the state of the control based on the `CheckState`.
     *
     * @param ctrl Pointer to the control.
     * @return A lambda function that takes a `CheckState` and sets the state of the control.
     */
    auto connector(C* ctrl)
    {
        return [&,ctrl](CheckState cs) { state_changer<C,bool>::set_state(cs.get()); };
    }

private:
    C* m_ctrl; ///< Pointer to the control.
};

}

template<typename C>
typename cogui::checkable<C>::CheckState::argument cogui::checkable<C>::checked;

#endif // CHECKABLE_H
