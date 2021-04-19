#ifndef BUTTON_H
#define BUTTON_H

#include "control.h"
#include "miso.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

namespace cogui {

class button : public control
{
public:

    button() = default;

    button(int x, int y, int width, int height, const std::wstring& title);
    button(int x, int y, int width, int height, const std::string& title);

    template<typename S, typename ... Args>
    button(int x, int y, int width, int height, const S& title, Args... args) : control(x, y, width, height, title)
    {
        init(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    void init(Args... args)
    {
        auto connector = overload_unref(
            [&,this](OnClick c) { miso::connect(this, sig_on_click, c.get()); }
        );

        auto tup = std::make_tuple(std::forward<Args>(args)...);

        for (auto const& elem : to_range(tup))
        {
            std::visit(connector, elem);
        }
    }

    void draw() const override;
    void click() override;

    int minimum_drawable_width() const override;
    int minimum_drawable_height() const override;

    using OnClick = fluent::NamedType<std::function<void(button*)>, struct OnClickHelper>;
    static OnClick::argument on_click;
    miso::signal<button*> sig_on_click{"on_click"};

};

}

#endif // BUTTON_H
