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
/**
 * @brief Manages the lifetime and execution flow of a cogui framework application.
 *
 * The application class provides essential control over application runtime, including
 * initialization, execution, and termination. It is responsible for handling the application
 * lifecycle from startup to shutdown.
 */
class application final
{
public:

    /**
     * @brief Constructs an application instance.
     *
     * Initializes the application with command-line arguments, allowing additional parameters
     * to be passed for configuration.
     *
     * @tparam Args Variadic template allowing additional arguments for extended configuration.
     * @param argc Argument count from the command-line.
     * @param argv Argument vector from the command-line.
     * @param args Additional arguments for application-specific setup.
     */
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


    /**
     * @brief Destructor for application.
     *
     * Cleans up resources associated with the application instance, ensuring an orderly shutdown.
     */
    ~application();

    /**
     * @brief Runs the application event loop.
     *
     * Starts the main loop of the application, managing events and control flow.
     * The function blocks until the application is signaled to stop.
     *
     * @return Exit code from the application run.
     */
    int run();

    /**
     * @brief Checks if the application is currently running.
     *
     * @return True if the application is in the running state, false otherwise.
     */
    bool running() const;

    /**
     * @brief Stops the application event loop.
     *
     * Signals the application to exit the main loop, initiating shutdown procedures.
     */
    void stop();

    /**
     * @brief Exits the application with a specified exit code.
     *
     * Terminates the application, returning a specified exit code to the operating system.
     *
     * @param c The exit code to return upon application termination (default is 0).
     */
    void exit(int c = 0);


private:
    application() = delete;
    application(const application&) = delete;
    application(application&&) = delete;

    application& operator = (const application&) = delete;
    application& operator = (application&&) = delete;


    //void handle_event(cogui::event c);
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
