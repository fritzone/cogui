#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "control.h"
#include "miso.h"
#include "desktop.h"
#include "theme.h"
#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "themeable.h"
#include "clickable.h"
#include "state_changer.h"
#include "checkable.h"

namespace cogui {


class checkbox : public themeable<checkbox>, public checkable<checkbox>
{
public:

	template<typename S>
	checkbox(int x, int y, int width, int height, const S& title) : themeable(x, y, width, height, title, this, builtin_checkbox_draw, builtin_checkbox_minimum_checkbox_width, builtin_checkbox_minimum_checkbox_height), checkable<checkbox>(this)
	{
	}

	template<typename S, typename ... Args>
	checkbox(int x, int y, int width, int height, const S& title, Args... args) :
		themeable(x, y, width, height, title, this, builtin_checkbox_draw, builtin_checkbox_minimum_checkbox_width, builtin_checkbox_minimum_checkbox_height),
		checkable<checkbox>(this)
	{
		if constexpr (sizeof... (args))
		{
			init(overload_unref(clickable<checkbox>::connector(this),
								state_changer<checkbox,bool>::connector(this),
								checkable<checkbox>::connector(this)),
				 std::forward<Args>(args)...);
		}
	}

	void click(int x, int y) override
	{
		checkable::click(this);
	}

};



}

#endif // CHECKBOX_H
