#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "cogui.h"
#include "rect.h"
#include "extension.h"

#include <string>
#include <functional>

namespace cogui
{

/**
 * @brief The graphics_engine class represents a mechanism that is used to draw the visual components of
 * the gui library onto the screen, after being rendered by the engine's renderer.
 *
 * Since this entire console gui framework was designed as a framework without the presence of a managed
 * graphical backend (ie. desktop environment) there is specific need for the graphical engines to provide
 * their own methods to properly handle the graphical work, such as double buffering, currently visible components'
 * drawing, frame rendering, which sometimes can feel like a really low level approach to certain functions
 * which you might feel granted when coming from a high level GUI background.
 *
 * In case a graphic engine does not support nor require double buffering just leave those methods empty.
 */
class rendering_engine : public extension
{
public:

	// These two variables are defined in a file generated by cmake
    static const char* type;
    static const char* path;

    /**
     * Default constructor and destructor for the base class
     */
    rendering_engine() noexcept = default;
    virtual ~rendering_engine() = default;

    /**
     * @brief name gives us the name of the graphics engine
     * @return the name of the graphics engine
     */
    virtual std::string name() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual void swap_buffers() = 0;
    virtual void present_scene() = 0;
    virtual bool start_rendering() = 0;
    virtual void set_rendering_function(std::function<bool()>) = 0;
    virtual void draw_text(int x, int y, wchar_t c, int flags) = 0;
    virtual void draw_text(int x, int y, const wchar_t* s, cogui::textflags flags = cogui::textflags::normal() ) = 0;

    virtual void refresh_screen() = 0;
    virtual void clear_screen() = 0;
    virtual void erase_screen() = 0;

    virtual void clear_area(int x, int y, int width, int height) = 0;

    virtual int get_screen_width() const = 0;
    virtual int get_screen_height() const = 0;

    virtual void set_fg_color(const color& c) = 0;
    virtual void set_bg_color(const color& c) = 0;
    virtual void set_colors(const color& fg, const color& bg) = 0;

	/**
	 * @brief set_clip_area Sets the clip area in which we can draw. Drawing outside of the clip area is not
	 * permitted, all visual artifacts going there should not be processed
	 * @param r the rect where the drawing is permittedl It has absolute desktop coordinates
	 */
	virtual void set_clip_area(const rect& r) = 0;

};

}

#endif // GRAPHICS_H