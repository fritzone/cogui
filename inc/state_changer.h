#ifndef STATE_CHANGER_H
#define STATE_CHANGER_H

#include "named_type.h"
#include "tuple_iterator.h"
#include "overload_impl.h"
#include "miso.h"

namespace cogui {

template<typename C, typename STATE> struct state_changer
{
    using OnStateChange= fluent::NamedType<std::function<void(C*,STATE)>, struct OnStateChangeHelper>;
    static typename OnStateChange::argument on_state_change;
    miso::signal<C*,STATE> sig_on_state_change{"on_state_change"};

    explicit state_changer(std::vector<STATE> states = {}) : m_states(states), m_state_index(0)
    {
        if(states.size() > 0)
        {
            m_state = states[0];
        }
    }

    auto connector(C* ctrl)
    {
        return [&,ctrl](OnStateChange s) { miso::connect(ctrl, sig_on_state_change, s.get()); };
    }

    void set_state(C* c, STATE s)
    {
        m_state = s;
        miso::internal::emitter<C>(*c) << sig_on_state_change(c, m_state);
    }

    void set_state(STATE s)
    {
        m_state = s;
    }

    STATE get_state() const
    {
        return m_state;
    }

    void set_next_state()
    {
        m_state_index ++;
        if(m_state_index == m_states.size()) m_state_index = 0;
        m_state = m_states[m_state_index];
    }

    STATE m_state{};
    std::vector<STATE> m_states;
    size_t m_state_index;
};

}

template<typename C, typename STATE>
typename cogui::state_changer<C,STATE>::OnStateChange::argument cogui::state_changer<C,STATE>::on_state_change;


#endif // STATE_CHANGER_H
