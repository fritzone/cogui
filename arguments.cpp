#include "arguments.h"

void cogui::arguments::argument_base::add_parameter(const std::string &a)
{
    if(!m_accepted_parameters.empty())
    {
        bool found = false;
        for(const auto& b : m_accepted_parameters)
        {
            log_debug() << "Checking" << b << "for" << name();
            if(b == a) {found = true;}
        }
        if(!found)
        {
            throw invalid_parameter(name(), a);
        }
    }
    m_parameters.push_back(a);
}

const std::vector<std::string> &cogui::arguments::argument_base::arguments() const
{
    return m_parameters;
}
