#ifndef APPLICATION_H
#define APPLICATION_H

#include "events.h"
#include "cogui.h"
#include "log.h"
#include "arguments.h"

#include <map>
#include <memory>
#include <iostream>

namespace cogui
{

/**
 * @brief init Initializes the cogui infrastructure
 *
 * @param argc the argc from main
 * @param argv the argv from main
 */
void init(int argc, char* argv[]);

/**
 * @brief The application class is responsible for the lifetime of an application using the cogui framework
 */
class application
{
public:

    /** Constructors */
    template<typename ... Args>
    application(int argc, char* argv[], Args&&... args)
    {
        try
        {
            log_info() << "application constructing or something";
            std::map<std::string, std::shared_ptr<arguments::argument_base>> gathered_arguments = handle_command_line(argc, argv);
            auto loop = [&gathered_arguments] (auto && input)
            {
                for(auto&[key, value] : gathered_arguments)
                {
                    if(input.is_same(key))
                    {
                        for(const auto& arg : value->arguments())
                        {
                            log_info() << "parameter: " << arg;
                            input.add_parameter(arg);
                        }
                        input.schedule_run();
                    }
                }

            };

            (loop(args), ...);

            cogui::init(argc, argv);

        }
        catch (const arguments::invalid_parameter& e)
        {
            std::cerr << e.what() << std::endl;
            print_help(std::forward<Args>(args)...);
            exit(1);
        }
    }

    application() = delete;
    application(const application&) = delete;
    application(application&&) = delete;

    application& operator = (const application&) = delete;
    application& operator = (application&&) = delete;

    int run();

    bool running() const;

    void stop();

    void exit(int c = 0);

private:
    void handle_event(cogui::event c);
    std::map<std::string, std::shared_ptr<arguments::argument_base>> handle_command_line(int argc, char*argv[]);

    template<typename ... Args>
    void print_help( Args&&... args )
    {
        auto loop = [](auto && input)
        {
            std::cout << input.help() << std::endl;
        };

        (loop(args), ...);
    }

private:
    bool m_running = false;
};

}

#endif // APPLICATION_H
