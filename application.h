#ifndef APPLICATION_H
#define APPLICATION_H

#include "events.h"
#include "cogui.h"
#include "log.h"
#include "arguments.h"

#include <map>
#include <memory>

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
        log_info() << "application constructing or something";
        cogui::init(argc, argv);

        std::map<std::string, std::shared_ptr<arguments::on_arg>> gathered_arguments;

        std::string current_flag;

        for(int i=1; i<argc; i++)
        {
            bool gathering_params = true;
            bool got_flag = false;
            int removed_minuses = 0;
            std::string carg = argv[i];
            std::string save_carg = carg;
            while(carg[0] == '-')
            {
                gathering_params = false;
                got_flag = true;
                carg = carg.substr(1);
                removed_minuses ++ ;
                if(removed_minuses > 2)
                {
                    throw "Invalid argument passing: " + save_carg;
                }
            }
            log_info() << carg << " saved:" << save_carg << " gather:" << gathering_params << " gotflag:" << got_flag << " current flag:" << current_flag;

            if(got_flag)
            {
                got_flag = false;
                current_flag = carg;
                gathered_arguments[current_flag] = std::make_shared<arguments::on_arg>(removed_minuses == 1 ? current_flag.c_str() : "", removed_minuses == 1 ? "" : current_flag);

            }
            else
            {
                if(gathering_params)
                {
                    gathered_arguments[current_flag]->add_argument(carg);
                }
                else
                {
                    gathering_params = true;
                }
            }

        }

        auto loop = [&gathered_arguments] (auto && input)
        {
            for(auto&[key, value] : gathered_arguments)
            {
                if(input.flag() == key)
                {
                    log_info() << "argument " << input.flag() << " key=" << key;
                    for(const auto& arg : value->arguments())
                    {
                        log_info() << "parameter: " << arg;
                        input.add_argument(arg);
                    }
                    input.schedule_run();
                }
            }

        };

        (loop(args), ...);
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

    bool m_running = false;
};

}

#endif // APPLICATION_H
