#ifndef ACTION_H
#define ACTION_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"
#include "string_type.h"
#include "key.h"

#include <string>

namespace cogui {


/**
 * @brief The action class represents an action that can be attached to a menu item, in order for it to
 * execute a user function or something similar
 */
class action
{
public:

    action() = default;
    action(action&&) = default;

    virtual ~action();
    action(const action& o);

    action& operator=(const action& o);
    action& operator=(action&& o) = default;


    template<cogui::StringType S, typename ... Args>
    void build(const S& title, cogui::key hotkey, Args... args)
    {
        m_title = convert_title(title);
        resolve_named_parameters(std::forward<Args>(args)...);
        determine_hotchar();
    }

    template<StringType S>
    action(const S& title)
    {
        m_title = convert_title(title);
    }

    template<StringType S, typename ... Args>
    action(const S& title, Args... args)
    {
        build(title, cogui::key::no_key, std::forward<Args>(args)...);
    }

    template<StringType S, typename ... Args>
    action(const S& title, cogui::key hotkey, Args... args)
    {
        build(title, hotkey, std::forward<Args>(args)...);
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

    template<StringType S>
    std::wstring convert_title(const S& title)
    {
        if constexpr (std::same_as<S, const char*> || std::same_as<S, std::string> || (std::is_array_v<S> && std::same_as<typename std::remove_extent<S>::type, char>))
        {
            return cogui::utils::std2ws(title);
        }
        else
        {
            return title;
        }
    }

	void determine_hotchar();

    std::wstring m_title;
    OnTrigger m_conn;
    bool m_checkable = false;
    bool m_checked = false;
	wchar_t m_hotchar = L'\0';
};

}

#endif // ACTION_H
