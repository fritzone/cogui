#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "control.h"
#include "miso.h"
#include "desktop.h"
#include "theme.h"
#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"


namespace cogui {

class checkbox : public control
{
public:

	checkbox(int x, int y, int width, int height, const std::string& title);
	checkbox(int x, int y, int width, int height, const std::wstring& title);

    template<typename S, typename ... Args>
    checkbox(int x, int y, int width, int height, const S& title, bool checked = false, Args... args) : control(x, y, width, height, title), m_checked(checked)
    {
		init(std::forward<Args>(args)...);
    }

	/**
	 * \section CheckboxSignals The signals emitted by a checkbox
	 */
	/**@{*/

	/**
	 * @brief The click of the checkbox emits two signals. The first one is the `on_click` and the second one
	 * is the `on_state_change`
	 */
	void click() override;

	/**
	 * \subsection CheckboxOnClick The on_click signal
	 *
	 * The `on_click` signal is emitted when the underlying architecture identified that a checkbox was clicked.
	 * A checkbox click is emitted when the mouse was pressed and released on the control. You can use a
	 * lambda function as the signal handler:
	 *
	 * \code{.cpp}
	 * auto win = cogui::window(5, 5, 70, 15, L"A test window");
	 * auto c = win.add_checkbox(35,5, 5, 2, L"Check me!", false,
	 *                           checkbox::on_click = [](checkbox* cb) {
	 *                                cb->set_title(cb->checked() ? L"Checked" : L"Unchecked");
	 *                            }
	 * );
	 * \endcode
	 *
	 * It is also possible to use a function as the signal handler:
	 *
	 * \code{.cpp}
	 * void chk_click_handler(cogui::checkbox* cb)
	 * {
	 *     cb->set_title(cb->checked() ? L"Checked" : L"Unchecked");
	 * }
	 * ....
	 * auto c = win.add_checkbox(35,5, 5, 2, L"Check me!", false,
	 *                           checkbox::on_click = chk_click_handler
	 * );
	 * \endcode
	 *
	 */
	/**@{*/
    using OnClick = fluent::NamedType<std::function<void(checkbox*)>, struct OnClickHelper>;
    static OnClick::argument on_click;
	miso::signal<checkbox*> sig_on_click{"on_click"};

    using OnStateChange= fluent::NamedType<std::function<void(checkbox*,bool)>, struct OnStateChangeHelper>;
    static OnStateChange::argument on_state_change;
    miso::signal<checkbox*,bool> sig_on_state_change{"on_state_change"};

    void setChecked(bool);
    bool checked() const;
    void check();
    void uncheck();

	CONTROL_INTEGRATION(checkbox)

private:

	template<typename ... Args>
	void init(Args... args)
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

private:

    bool m_checked = false;

};

}

#endif // CHECKBOX_H
