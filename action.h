#ifndef ACTION_H
#define ACTION_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

#include <string>

namespace cogui {

class action
{
public:

    action() = default;
    action(action&&) = default;

    virtual ~action();
    action(const action& o);

    action& operator=(const action& o);
    action& operator=(action&& o) = default;

    action(const std::wstring& title) : m_title(title)
    {
    }

    template<typename ... Args>
    action(const std::wstring& title, Args... args) : m_title(title)
    {
        resolve_named_parameters(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    action(const std::wstring& title, cogui::key hotkey, Args... args) : m_title(title)
    {
        resolve_named_parameters(std::forward<Args>(args)...);
    }



    void trigger();
    std::wstring getTitle() const;
    void setTitle(const std::wstring &getTitle);

    // triggering signal
    using OnTrigger = fluent::NamedType<std::function<void(action*)>, struct OnTriggerHelper>;
    static OnTrigger::argument on_trigger;
    miso::signal<action*> sig_on_trigger {"on_trigger"};

    // whether it is selectable or not
    using Selectable = fluent::NamedType<bool, struct OnSelectableHelper>;
    static Selectable::argument selectable;

    bool isSelectable() const;

    template<typename ... Args>
    void resolve_named_parameters(Args... args)
    {
        auto connector = overload_unref(
            [&,this](OnTrigger c) { m_conn = c; miso::connect(this, sig_on_trigger, c.get()); },
            [&,this](Selectable s) {m_selectable = s.get(); log_debug() << (m_selectable ? "SSSSSSSSSSSSSSSS" : "XXXXXXXXXXXXXxxx");}
        );

        auto tup = std::make_tuple(std::forward<Args>(args)...);

        for (auto const& elem : to_range(tup))
        {
            std::visit(connector, elem);
        }
    }

private:
    std::wstring m_title;
    OnTrigger m_conn;
    bool m_selectable = false;
    bool m_selected = false;
};

}

#endif // ACTION_H
