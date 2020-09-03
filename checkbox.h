#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "control.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

namespace cogui {

class checkbox : public control
{
public:

    checkbox(int getX, int getY, int getWidth, int getHeight, const std::wstring& getTitle);

    template<typename ... Args>
    checkbox(int x, int y, int width, int height, const std::wstring& title, bool checked = false, Args... args) : control(x, y, width, height, title), m_checked(checked)
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
    int minimumDrawableHeight() const override;

    using OnClick = fluent::NamedType<std::function<void(checkbox*)>, struct OnClickHelper>;
    static OnClick::argument on_click;
    miso::signal<checkbox*> sig_on_click;

    bool checked() const;

private:

    bool m_checked = false;

};

}

#endif // CHECKBOX_H