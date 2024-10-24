#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

namespace cogui {

template<typename C> struct clickable
{
    using OnClick = fluent::NamedType<std::function<void(C*)>, struct OnClickHelper>;
    static typename OnClick::argument on_click;
    miso::signal<C*> sig_on_click{"on_click"};

    void click(C* c)
    {
        miso::internal::emitter<C>(*c) << sig_on_click(c);
    }

    auto connector(C* ctrl)
    {
        return [&,ctrl](OnClick c) { miso::connect(ctrl, sig_on_click, c.get()); };
    }
};

template<typename C>
typename cogui::clickable<C>::OnClick::argument cogui::clickable<C>::on_click;

}

#endif // CLICKABLE_H
