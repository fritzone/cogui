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
		determine_hotchar();
    }

    template<typename ... Args>
    action(const std::wstring& title, Args... args) : m_title(title)
    {
        resolve_named_parameters(std::forward<Args>(args)...);
		determine_hotchar();
    }

    template<typename ... Args>
    action(const std::wstring& title, cogui::key hotkey, Args... args) : m_title(title)
    {
        resolve_named_parameters(std::forward<Args>(args)...);
		determine_hotchar();
    }

    void trigger();
	void check();
    std::wstring get_title() const;
    void set_title(const std::wstring &getTitle);

    // triggering signal
    using OnTrigger = fluent::NamedType<std::function<void(action*)>, struct OnTriggerHelper>;
    static OnTrigger::argument on_trigger;
    miso::signal<action*> sig_on_trigger {"on_trigger"};

    // whether it is selectable or not
    using Checkable = fluent::NamedType<bool, struct OnCheckableHelper>;
    static Checkable::argument checkable;

    // and if it's whether it's selected or not
    using Checked = fluent::NamedType<bool, struct OnSelectableHelper>;
    static Checked::argument checked;

    bool is_checkable() const;
    bool is_checked() const;
	wchar_t hotchar() const;
    bool is_separator() const;

    template<typename ... Args>
    void resolve_named_parameters(Args... args)
    {
        auto connector = overload_unref(
            [&,this](OnTrigger c) {m_conn = c; miso::connect(this, sig_on_trigger, c.get()); },
            [&,this](Checkable s) {m_checkable = s.get(); }
        );

        auto tup = std::make_tuple(std::forward<Args>(args)...);

        for (auto const& elem : to_range(tup))
        {
            std::visit(connector, elem);
        }
    }

private:
	void determine_hotchar();

    std::wstring m_title;
    OnTrigger m_conn;
    bool m_checkable = false;
    bool m_checked = false;
	wchar_t m_hotchar = L'\0';
};

}

#endif // ACTION_H
