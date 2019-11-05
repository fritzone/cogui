#ifndef BUTTON_H
#define BUTTON_H

#include "control.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

namespace cogui {

class button : public control
{
public:

    button(int getX, int getY, int getWidth, int getHeight, const std::wstring& getTitle);

    template<typename ... Args>
    button(int x, int y, int width, int height, const std::wstring& title, Args... args) : control(x, y, width, height, title)
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

    int minimumDrawableWidth() const override;


    using OnClick = fluent::NamedType<std::function<void(button*)>, struct OnClickHelper>;
    static OnClick::argument on_click;

    miso::signal<button*> sig_on_click;

};

}

#endif // BUTTON_H