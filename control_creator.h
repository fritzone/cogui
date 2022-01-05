#ifndef CONTROL_CREATOR_H
#define CONTROL_CREATOR_H

#include <memory>

namespace cogui {

template<class C>
struct control_creator
{
    using CREATOR = control_creator<C>;

    control_creator() = default;

    template<typename S, typename ... Args>
    control_creator(const S& s, Args... args)
    {
        m_control = new C(s, std::forward<Args>(args)...);
    }

    C* get_control() const
    {
        return m_control;
    }

    C* m_control;

};

}

#endif // CONTROL_CREATOR_H
