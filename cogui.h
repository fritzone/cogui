#ifndef COGUI_H
#define COGUI_H

#include "application.h"
#include "window.h"
#include "button.h"
#include "menu.h"
#include "arguments.h"
#include "desktop.h"
#include "control.h"
#include "checkbox.h"
#include "graphics_engine.h"
#include "log.h"
#include "utils.h"

namespace cogui {

    /**
     * @brief MAX_CAPTION_WIDTH The maximum width of the captions for each of the UI elements
     */
    static const int MAX_CAPTION_WIDTH = 256;

    /**
     * @brief graphics will return the current graphics engine.
     * @return the current graphics engine
     */
    std::shared_ptr<graphics_engine> graphics();

}

#endif // COGUI_H
