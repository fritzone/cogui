#ifndef LABEL_H
#define LABEL_H

#include "control.h"
#include "desktop.h"
#include "theme.h"
#include "themeable.h"

namespace cogui {


/**
 * @brief The label class represents a label that can display textual information
 *
 * auto l = win.add_label(35, 5, 5, 2, "Label me");
 * \endcode
 *
 */
class label : public themeable<label>
{
public:

    /**
     * @brief Create a label at the given position, with the given string title
     *
     * @param x - the X position of the label (relative to its parent window)
     * @param y - the Y position of the label (relative to its parent window)
     * @param width - the width of the label
     * @param height - the height of the label
     * @param title - the text that will be shown on the button - string
     */
    template<typename S>
    label(int x, int y, int width, int height, const S& title) :
        themeable(x, y, width, height, title, this, builtin_label_draw, builtin_label_minimum_label_width, builtin_label_minimum_label_height)
    {}

    void click(int,int) override {}

};

}

#endif // LABEL_H
