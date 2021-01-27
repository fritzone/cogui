#include "key.h"
#include "events.h"

cogui::key cogui::key::F1( {cogui::events::key_class::key_f1, false, false, false, L"F1"} );
template<> cogui::key& cogui::on<&cogui::key::F1>::press = cogui::key::F1;

cogui::key cogui::key::F2( {cogui::events::key_class::key_f2, false, false, false, L"F2"} );
template<> cogui::key& cogui::on<&cogui::key::F2>::press = cogui::key::F2;

cogui::key cogui::key::F3( {cogui::events::key_class::key_f3, false, false, false, L"F3"} );
template<> cogui::key& cogui::on<&cogui::key::F3>::press = cogui::key::F3;

cogui::key cogui::key::F4( {cogui::events::key_class::key_f4, false, false, false, L"F4"} );
template<> cogui::key& cogui::on<&cogui::key::F4>::press = cogui::key::F4;

cogui::key cogui::key::F5( {cogui::events::key_class::key_f5, false, false, false, L"F5"} );
template<> cogui::key& cogui::on<&cogui::key::F5>::press = cogui::key::F5;

cogui::key cogui::key::F6( {cogui::events::key_class::key_f6, false, false, false, L"F6"} );
template<> cogui::key& cogui::on<&cogui::key::F6>::press = cogui::key::F6;

cogui::key cogui::key::F7( {cogui::events::key_class::key_f7, false, false, false, L"F7"} );
template<> cogui::key& cogui::on<&cogui::key::F7>::press = cogui::key::F7;

cogui::key cogui::key::F8( {cogui::events::key_class::key_f8, false, false, false, L"F8"} );
template<> cogui::key& cogui::on<&cogui::key::F8>::press = cogui::key::F8;

cogui::key cogui::key::F9( {cogui::events::key_class::key_f9, false, false, false, L"F9"} );
template<> cogui::key& cogui::on<&cogui::key::F9>::press = cogui::key::F9;

cogui::key cogui::key::F10( {cogui::events::key_class::key_f10, false, false, false, L"F10"} );
template<> cogui::key& cogui::on<&cogui::key::F10>::press = cogui::key::F10;

cogui::key cogui::key::F11( {cogui::events::key_class::key_f11, false, false, false, L"F11"} );
template<> cogui::key& cogui::on<&cogui::key::F11>::press = cogui::key::F11;

cogui::key cogui::key::F12( {cogui::events::key_class::key_f12, false, false, false, L"F12"} );
template<> cogui::key& cogui::on<&cogui::key::F12>::press = cogui::key::F12;


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
