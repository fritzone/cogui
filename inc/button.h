#ifndef BUTTON_H
#define BUTTON_H

#include "control.h"
#include "desktop.h"
#include "theme.h"
#include "clickable.h"
#include "themeable.h"
#include "string_type.h"

namespace cogui {


/**
 * @brief The button class represents a push button control that a user can interact with by pressing it.
 *
 * \section ButtonSignals The signals emitted by a button
 * \subsection ButtonOnClick The on_click signal
 *
 * The `on_click` signal is emitted when the underlying architecture identified that a button was clicked.
 * A button click is emitted when the mouse was pressed and released on the control. You can use a
 * lambda function as the signal handler:
 *
 * \code{.cpp}
 *  auto win = cogui::window(5, 5, 70, 15, L"A test window");
 *  auto c = win.add_button(35, 5, 20, 2, L"&Horizontal layout",
 *	                    button::on_click = [&win](button* btn){
 *                           win.set_layout<cogui::layout::horizontal>();
 *                      }
 * );
 * \endcode
 *
 * It is also possible to use a function as the signal handler:
 *
 * \code{.cpp}
 * void b_handler(cogui::button* b)
 * {
 *     b->set_title(L"Clicked");
 * }
 * ....
 * auto b = win.add_button(35,5, 5, 2, L"C", button::on_click = b_handler);
 * \endcode
 *
 */
class button : public themeable<button>, public clickable<button>
{
public:

	/**
	 * @brief Create a button at the given position, with the given string title
	 *
	 * @param x - the X position of the button (relative to its parent window)
	 * @param y - the Y position of the button (relative to its parent window)
	 * @param width - the width of the button
	 * @param height - the height of the button
	 * @param title - the text that will be shown on the button - string
	 */
    template<StringType S>
	button(int x, int y, int width, int height, const S& title) : themeable(x, y, width, height, title, this, builtin_button_draw, builtin_button_minimum_button_width, builtin_button_minimum_button_height) {}

	/**
	 * @brief Create a button at the given position, with the given title and the possible signal connections.
	 *
	 * You use this constructor as:
	 *
	 * \code{.cpp}
	 *  auto win = cogui::window(5, 5, 70, 15, L"A test window");
	 *  auto c = win.add_button(35, 5, 20, 2, L"&Horizontal layout",
	 *	                    button::on_click = [&win](button* btn){
	 *                           win.set_layout<cogui::layout::horizontal>();
	 *                      }
	 * );
	 * \endcode
	 *
	 * At this stage there is one signal for the button class: `on_click` which takes the button that
	 * emitted it as parameter.
	 *
	 * @param x - the X position of the button (relative to its parent window)
	 * @param y - the Y position of the button (relative to its parent window)
	 * @param width - the width of the button
	 * @param height - the height of the button
	 * @param title - the text that will be shown on the button - widestring or ansi string
	 * @param args - the signal handlers of the button
	 */
    template<StringType S, typename ... Args>
	button(int x, int y, int width, int height, const S& title, Args... args) : themeable(x, y, width, height, title, this, builtin_button_draw, builtin_button_minimum_button_width, builtin_button_minimum_button_height)
    {
		if constexpr (sizeof... (args))
		{
			init(overload_unref(clickable::connector(this)) , std::forward<Args>(args)...);
		}
	}

	/**
	 * @brief The click of the button emits the given on_click signal. Called by the underlying architecture
	 */
	void click(int x, int y) override
	{
		clickable::click(this);
	}

};

}

#endif // BUTTON_H
