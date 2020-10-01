#include "key.h"
#include "events.h"

cogui::key cogui::key::F2( {cogui::events::key_class::key_f2, false, false, false, L"F2"} );

cogui::key::key(const cogui::events::keypress &generator): m_generator(generator)
{
}

cogui::key cogui::key::operator +(const cogui::key &other)
{

    // we can create a hotkey only if one of the keys is a modifier
    if(m_generator.get_type() != cogui::events::key_class::key_modifier && other.m_generator.get_type() != cogui::events::key_class::key_modifier)
    {
        throw "Cannot create a hotkey with this combination";
    }

    key result;
    result.m_generator.set_alt_modifier(m_generator.get_alt() || other.m_generator.get_alt());
    result.m_generator.set_ctrl_modifier(m_generator.get_ctrl() || other.m_generator.get_ctrl());
    result.m_generator.set_shift_modifier(m_generator.get_shift() || other.m_generator.get_shift());

    if(m_generator.get_type() != cogui::events::key_class::key_modifier)
    {
        result.m_generator.set_chardata(m_generator.get_chardata());
        result.m_generator.set_type(m_generator.get_type());
    }
    else
    if(other.m_generator.get_type() != cogui::events::key_class::key_modifier)
    {
        result.m_generator.set_chardata(other.m_generator.get_chardata());
        result.m_generator.set_type(other.m_generator.get_type());
    }
    else
    {
        result.m_generator.set_type(cogui::events::key_class::key_modifier);
    }

    result.m_generator.set_as_hotkey();

    return result;
}


