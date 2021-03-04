#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "control.h"
#include "miso.h"

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"

namespace cogui {

class checkbox : public control
{
public:

    checkbox(int getX, int getY, int getWidth, int getHeight, const std::wstring& getTitle);

    template<typename S, typename ... Args>
    checkbox(int x, int y, int width, int height, const S& title, bool checked = false, Args... args) : control(x, y, width, height, title), m_checked(checked)
    {
        auto connector = overload_unref(
            [&,this](OnClick c) { miso::connect(this, sig_on_click, c.get()); },
            [&,this](OnStateChange s) { miso::connect(this, sig_on_state_change, s.get()); }
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

    // on click signal
    using OnClick = fluent::NamedType<std::function<void(checkbox*)>, struct OnClickHelper>;
    static OnClick::argument on_click;

    // state change signal
    using OnStateChange= fluent::NamedType<std::function<void(checkbox*,bool)>, struct OnStateChangeHelper>;
    static OnStateChange::argument on_state_change;

    miso::signal<checkbox*> sig_on_click{"on_click"};
    miso::signal<checkbox*,bool> sig_on_state_change{"on_state_change"};

    void setChecked(bool);
    bool checked() const;
    void check();
    void uncheck();

private:

    bool m_checked = false;

};

}

#endif // CHECKBOX_H
