#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>
#include "log.h"

namespace cogui {

namespace arguments {

enum class required
{
    always = 0,
    sometimes = 1
};

namespace parameters
{
enum class separated
{
    by_comma = 0,
    by_space = 1
};
} // namespace parameters

class on_command final
{
public:
    on_command(const char* command = "", const std::string& help = "", required par_req = required::sometimes, parameters::separated par_sp = parameters::separated::by_space)
    {
        log_info() << "created on_arg for:" << command;
    }

    on_command& operator = (const on_command&) = delete;
    on_command(const on_command&)  = delete;
};

class on_arg final
{
public:
    on_arg(const char *argn, const std::string& help = "", const char* longn = "", required par_req = required::sometimes, parameters::separated par_sp = parameters::separated::by_space) : m_arg(argn), m_longn(longn), m_help(help), m_arguments(), m_req(par_req), m_par_sp(par_sp)
    {
        log_info() << "created on_arg for:" << argn;
    }

    on_arg& operator = (const on_arg&) = delete;
    on_arg& operator = (on_arg&&) = delete;
    on_arg(const on_arg&)  = delete;
    on_arg(const on_arg&&)  = delete;

    ~on_arg()
    {
        if(m_need_run)
        {
            m_ae->execute(m_arguments);
        }
    }

    struct arg_executor
    {
        virtual void execute(const std::vector<std::string>& arguments) = 0;
    };

    template<typename T> struct arg_executor_t : public arg_executor
    {
        arg_executor_t(const T& t) : m_t(t)
        {
        }

        virtual void execute(const std::vector<std::string>& arguments) override
        {
            m_t(arguments);
        }

        const T& m_t;

    };

    std::string flag() const
    {
        return m_arg;
    }

    std::string longflag() const
    {
        return m_longn;
    }

    template<typename T>
    on_arg& operator = (const T& a)
    {
        static arg_executor_t<T> t(a);
        m_ae = &t;
        return *this;
    }

    void add_argument(const std::string& a)
    {
        m_arguments.push_back(a);
    }

    void schedule_run()
    {
        m_need_run = true;
    }

    const std::vector<std::string>& arguments() const
    {
        return m_arguments;
    }

private:
    std::string m_arg;
    std::string m_longn;
    std::string m_help;
    arg_executor* m_ae = nullptr;
    std::vector<std::string> m_arguments;
    required m_req;
    parameters::separated m_par_sp;
    bool m_need_run = false;
};


}
}
#endif // ARGUMENTS_H
