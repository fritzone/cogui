#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>
#include <algorithm>

#include "log.h"

namespace cogui {

namespace arguments {

class invalid_parameter : public std::exception
{
public:

    invalid_parameter(const std::string& argument, const std::string parameter) : m_message ("Invalid parameter " + parameter + " for argument " + argument)
    {
    }

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }

private:

    std::string m_message;
};

enum class role
{
    always_required = 0,
    sometimes_required = 1,
    help = 2
};

using accepted_parameters = std::vector<std::string>;

class argument_base
{
public:

    explicit argument_base(const std::string& help = "", accepted_parameters ap = {}, role par_req = role::sometimes_required) : m_req(par_req), m_accepted_parameters(ap), m_help(help)
    {}

    argument_base& operator = (const argument_base&) = delete;
    argument_base& operator = (argument_base&&) = delete;
    argument_base(const argument_base&)  = delete;
    argument_base(const argument_base&&)  = delete;

    virtual ~argument_base()
    {
        if(m_need_run)
        {
            m_ae->execute(m_parameters);
        }
    }

    /** tells us if this argument is the same as the one sent in as the parameter. The long flag is the reason for
     * the existence of this method */
    virtual bool is_same(const std::string&) = 0;

    /* the name of the argument */
    virtual std::string name() = 0;

    void add_parameter(const std::string& a);

    void schedule_run()
    {
        m_need_run = true;
    }

    const std::vector<std::string>& arguments() const;

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

    std::string help()
    {
        std::string result = "-" + name() + " " + m_help;
        return result;
    }

protected:

    std::vector<std::string> m_parameters;
    arg_executor* m_ae = nullptr;
    role m_req;
    bool m_need_run = false;
    std::vector<std::string> m_accepted_parameters;
    std::string m_help;

};

/**
 * @brief The on_command class represents a command sent in to the application. Commands do not start
 * with a "-", for example: apt-get install. If the required_parameters is -1 all the argv values after will be
 * treated as parameters of this command, till the first flag (starts with "-") appears or till another command is
 * identifed in the argv list.
 */
class on_command final : public argument_base
{
public:
    on_command(const char* command = "", const std::string& help = "", accepted_parameters ap = {}, role par_req = role::sometimes_required, int required_parameters = -1) : argument_base(help, ap, par_req)
    {
        log_info() << "created on_arg for:" << command;
    }

    on_command(const on_command&)  = delete;
    on_command(on_command&&)  = delete;
    on_command& operator = (const on_command&) = delete;
    on_command& operator = (on_command&&) = delete;
};

/**
 * @brief The on_flag class represents a flag sent into the application. Flags always start with a "-" (short flag)
 * or "--" long flag. More than 2 "-"s will be rejected. Flags may have parameters, in the parsing all the argv
 * values will be treates as parameters till the next flag (starts with "-") appears or till a command is found
 * in the argv list
 */
class on_flag final : public argument_base
{
public:
    on_flag(const char *argn, const std::string& help = "", accepted_parameters ap = {}, role par_req = role::sometimes_required, const char* longn = "") : argument_base(help, ap, par_req), m_arg(argn), m_longn(longn)
    {
        log_info() << "created on_arg for:" << argn;
    }

    bool is_same(const std::string& c) override
    {
        return m_arg == c || m_longn == c;
    }

    std::string name() override
    {
        return m_arg.empty() ? m_longn : m_arg;
    }

    template<typename T>
    on_flag& operator = (const T& a)
    {
        static arg_executor_t<T> t(a);
        m_ae = &t;
        return *this;
    }

private:
    std::string m_arg;
    std::string m_longn;

};


}
}
#endif // ARGUMENTS_H
