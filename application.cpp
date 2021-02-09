#include "application.h"
#include "desktop.h"
#include "mouse.h"
#include "window.h"
#include "input.h"
#include "events.h"

#include "log.h"

cogui::application::~application()
{
    desktop::get().shutdown();
}

int cogui::application::run()
{
    m_running = true;

    // firstly let's get a clear desktop
    desktop::get().redraw();

    desktop::get().getGraphics()->present_scene();
    desktop::get().getGraphics()->swapBuffers();

    desktop::get().getGraphics()->refresh_screen();
    desktop::get().getGraphics()->erase_screen();

    // then enter the loop
    while( running() )
    {
        desktop::get().getGraphics()->present_scene();
        desktop::get().getGraphics()->swapBuffers();

        auto events = desktop::get().getInput()->get_next_event();
        bool handled = false;
        for(auto c : events)
        {
            if(c->handle())
            {
                handled = true;
                desktop::get().getGraphics()->refresh_screen();
                desktop::get().getGraphics()->erase_screen();

                desktop::get().getGraphics()->present_scene();
                desktop::get().getGraphics()->swapBuffers();
            }
        }

        if(!handled)
        {
            desktop::get().getGraphics()->refresh_screen();
            desktop::get().getGraphics()->erase_screen();
        }
    }
    return 1;
}

bool cogui::application::running() const
{
    return m_running;
}

void cogui::application::stop()
{
    m_running = false;
}

void cogui::application::exit(int c)
{
    stop();
    ::exit(c);
}

/*
void cogui::application::handle_event(cogui::event c)
{

    switch(c)
    {
        case cogui::event::press_escape:
        {
            log_debug() << "Escape";
            exit(1);
        }
        case cogui::event::press_tab:
        {
            desktop::get().handle_tab();
            break;
        }
        case cogui::event::mouse_left_click:
        {
            log_debug() << "left click: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_click(mouse::get().x(), mouse::get().y());
            break;
        }
        case cogui::event::mouse_left_press:
        {
            log_debug() << "left press: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_down(mouse::get().x(), mouse::get().y());
            break;
        }
        case cogui::event::mouse_left_release:
        {
            log_debug() << "left release: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_left_up(mouse::get().x(), mouse::get().y());
            break;
        }
        case cogui::event::mouse_move:
        {
            log_debug() << "move: " << mouse::get().x() << "x" << mouse::get().y();
            desktop::get().handle_mouse_move(mouse::get().x(), mouse::get().y());
            break;
        }
    }
}*/

std::map<std::string, std::shared_ptr<cogui::arguments::argument_base> > cogui::application::handle_command_line(int argc, char *argv[], std::string& theme)
{
    std::map<std::string, std::shared_ptr<arguments::argument_base>> gathered_arguments;
    std::string current_flag;
    std::string current_command;

    for(int i=1; i<argc; i++)
    {
        bool gathering_params = true;
        bool got_flag = false;
        int removed_minuses = 0;
        std::string carg = argv[i];
        std::string save_carg = carg;

        if(carg == "--theme") // builtin argument for selecting the theme
        {
            if(i + 1 < argc)
            {
                theme = argv[i + 1];
                i++;
                continue;
            }
            else
            {
                throw cogui::arguments::invalid_parameter("Argument --theme requires a parameter, the name of the theme", "--theme");
            }
        }

        while(carg[0] == '-')
        {
            gathering_params = false;
            got_flag = true;
            carg = carg.substr(1);
            removed_minuses ++ ;
            if(removed_minuses > 2)
            {
                throw cogui::arguments::invalid_parameter("Invalid argument passing", save_carg);
            }
        }
        log_info() << carg << " saved:" << save_carg << " gather:" << gathering_params << " gotflag:" << got_flag << " current flag:" << current_flag;

        if(got_flag)
        {
            got_flag = false;
            current_flag = carg;
            gathered_arguments[current_flag] = std::make_shared<arguments::on_flag>(removed_minuses == 1 ? current_flag.c_str() : "", removed_minuses == 1 ? "" : current_flag);
        }
        else
        {
            if(gathering_params)
            {
                gathered_arguments[current_flag]->add_parameter(carg);
            }
            else
            {
                gathering_params = true;
            }
        }
    }
    return gathered_arguments;
}
