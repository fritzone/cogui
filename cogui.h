#ifndef COGUI_H
#define COGUI_H

#include <memory>

namespace cogui {

    class graphics_engine;

    /**
     * @brief MAX_CAPTION_WIDTH The maximum width of the captions for each of the UI elements
     */
    static const int MAX_CAPTION_WIDTH = 256;

    // the application will return this value if it cannot initialize the graphic engine
    static const int UNABLE_TO_INITIALIZE_GRAPHICS = 211;

    /**
     * @brief graphics will return the current graphics engine.
     * @return the current graphics engine
     */
    std::shared_ptr<graphics_engine> graphics();

    class color
    {
    public:

        color(uint8_t c) : m_value(c) {}

        static const uint8_t black = 1;
        static const uint8_t red = 2;
        static const uint8_t green = 3;
        static const uint8_t yellow = 4;
        static const uint8_t blue = 5;
        static const uint8_t magenta = 6;
        static const uint8_t cyan = 7;
        static const uint8_t white = 8;

        operator uint8_t() const
        {
            return m_value;
        }
    private:
        uint8_t m_value;
    };

    using foreground_color = color;
    using background_color = color;


    class textflags
    {
    public:
        enum value : uint64_t
        {
            v_normal = 0,
            v_bold = 1 << 9,
            v_underline = 1 << 13,
            v_title = 1 << 22
        };

        static textflags normal;
        static textflags bold;
        static textflags underline;
        static textflags title;

        textflags() = default;

        textflags(value a) : m_value(a) { }
        textflags(int a) : m_value(a) { }

        int operator &(const textflags& o) const;

        operator int() const;

    private:
        int m_value;
    };


}

#include "application.h"
#include "window.h"
#include "button.h"
#include "action.h"
#include "menu.h"
#include "menubar.h"
#include "arguments.h"
#include "desktop.h"
#include "control.h"
#include "checkbox.h"
#include "graphics_engine.h"
#include "log.h"
#include "utils.h"
#include "key.h"
#include "scrollbar.h"
#include "color.h"

#endif // COGUI_H
