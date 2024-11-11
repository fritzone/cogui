#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

namespace cogui {

/**
 * @struct clickable
 * @brief A template struct that provides clickable functionality to a control.
 *
 * The `clickable` struct adds click event handling capabilities to a control.
 * It manages click signals and connections using the `miso` library and provides
 * an interface to handle click events.
 *
 * @tparam C The type of the control to which clickable functionality is added.
 */
template<typename C>
struct clickable {

    // the connection to the named parameter
    using OnClick = fluent::NamedType<std::function<void(C*)>, struct OnClickHelper>;
    static typename OnClick::argument on_click;

    /**
     * @var sig_on_click
     * @brief A signal object to manage click events.
     */
    miso::signal<C*> sig_on_click{"on_click"};

    /**
     * @brief Handles the click event for the control.
     *
     * Emits the click signal when the control is clicked.
     *
     * @param c Pointer to the control.
     */
    void click(C* c)
    {
        miso::internal::emitter<C>(*c) << sig_on_click(c);
    }

    /**
     * @brief Creates a connector function for the control.
     *
     * The connector function can be used to connect a click handler to the control's click signal.
     *
     * @param ctrl Pointer to the control.
     * @return A lambda function that takes an `OnClick` handler and connects it to the click signal.
     */
    auto connector(C* ctrl)
    {
        return [&,ctrl](OnClick c) { miso::connect(ctrl, sig_on_click, c.get()); };
    }
};


template<typename C>
typename cogui::clickable<C>::OnClick::argument cogui::clickable<C>::on_click;

}

#endif // CLICKABLE_H
