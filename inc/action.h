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
 * @brief Represents an action that can be associated with a menu item, allowing
 * it to execute a user-defined function or similar operation when triggered.
 *
 * This class provides a variety of constructors to initialize an action with optional parameters
 * such as title, hotkey, and callback functions. It supports functionalities for
 * setting checkable properties, defining triggers, and managing menu item states.
 *
 * While working with cogui you will not need to directly create actions, because
 * the menu constructor handles creating actions gratiously, like the example below:
 *
 * @code
 * menu {
 *   "&File", {
 *     {"&New",  action::on_trigger = [](action*){log_info() << "New Clicked";}}
 *   }
 * }
 * @endcode
 *
 */
class action
{
public:

    /**
     * @brief Default constructor for action.
     *
     * Constructs an empty action with no title or trigger.
     */
    action() = default;

    /**
     * @brief Move constructor.
     *
     * Allows the action to be moved without copying internal data, for optimized performance.
     */
    action(action&&) = default;

    /**
     * @brief Destructor for action.
     *
     * Cleans up any allocated resources and connections.
     */
    virtual ~action();

    /**
     * @brief Copy constructor.
     *
     * Creates a copy of an existing action, duplicating the title, hotkey, and any parameters.
     *
     * @param o Another action object to copy.
     */
    action(const action& o);

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the contents of one action to another, replacing any existing values.
     *
     * @param o Another action object to assign from.
     * @return Reference to the current action after assignment.
     */
    action& operator=(const action& o);

    /**
     * @brief Move assignment operator.
     *
     * Transfers ownership of resources from one action to another.
     *
     * @param o Another action object to move from.
     * @return Reference to the current action after assignment.
     */
    action& operator=(action&& o) = default;

    /**
     * @brief Constructs an action with a title.
     *
     * Converts the title to a wide string if necessary.
     *
     * @tparam S Type of the title, expected to satisfy StringType.
     * @param title The title text for the action.
     */
    template<StringType S>
    action(const S& title)
    {
        m_title = convert_title(title);
    }

    /**
     * @brief Constructs an action with a title and additional parameters.
     *
     * Configures the title and allows additional parameters like checkable and trigger.
     *
     * @tparam S Type of the title.
     * @tparam Args Parameter pack for additional named parameters.
     * @param title Title for the action.
     * @param args Additional parameters for configuring the action.
     */
    template<StringType S, typename ... Args>
    action(const S& title, Args... args)
    {
        build(title, cogui::key::no_key, std::forward<Args>(args)...);
    }

    /**
     * @brief Constructs an action with a title, hotkey, and additional parameters.
     *
     * Allows specification of a hotkey and additional settings for the action.
     *
     * @tparam S Type of the title.
     * @tparam Args Parameter pack for additional named parameters.
     * @param title Title for the action.
     * @param hotkey A key associated with the action for quick access.
     * @param args Additional parameters for configuring the action.
     */
    template<StringType S, typename ... Args>
    action(const S& title, cogui::key hotkey, Args... args)
    {
        build(title, hotkey, std::forward<Args>(args)...);
    }

    /**
     * @brief Triggers the action.
     *
     * Executes any attached function associated with the action, signaling it has been activated.
     */
    void trigger();

    /**
     * @brief Checks the action's current state.
     *
     * Verifies if the action meets certain criteria, such as being selected.
     */
    void check();

    /**
     * @brief Gets the title of the action.
     *
     * @return The title as a wide string.
     */
    std::wstring get_title() const;

    /**
     * @brief Sets the title of the action.
     *
     * Allows updating the action's title.
     *
     * @param getTitle The new title for the action.
     */
    void set_title(const std::wstring &getTitle);

    /**
     * @brief Determines if the action is checkable.
     *
     * @return True if the action is checkable, false otherwise.
     */
    bool is_checkable() const;

    /**
     * @brief Checks if the action is currently checked.
     *
     * @return True if the action is checked, false otherwise.
     */
    bool is_checked() const;

    /**
     * @brief Gets the hotkey character.
     *
     * @return The character associated with the action's hotkey.
     */
    wchar_t hotchar() const;

    /**
     * @brief Checks if the action is a separator.
     *
     * Separator actions do not respond to triggers and serve as dividers.
     *
     * @return True if the action is a separator, false otherwise.
     */
    bool is_separator() const;

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
    template<cogui::StringType S, typename ... Args>
    void build(const S& title, cogui::key hotkey, Args... args)
    {
        m_title = convert_title(title);
        resolve_named_parameters(std::forward<Args>(args)...);
        determine_hotchar();
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
