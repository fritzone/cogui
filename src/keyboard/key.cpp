#include "key.h"
#include "events.h"

namespace cogui
{
// No key as hotkey
const key key::no_key {};


// Key A
template<> cogui::key& cogui::on_impl<NoMod_a>::press = (NoMod_a::ptrNoMod_a)();
template<> cogui::key& cogui::on_impl<Shift_a>::press = (Shift_a::ptrShift_a)();
template<> cogui::key& cogui::on_impl<Ctrl_a>::press = (Ctrl_a::ptrCtrl_a)();
template<> cogui::key& cogui::on_impl<Alt_a>::press = (Alt_a::ptrAlt_a)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_a>::press = (Ctrl_Alt_a::ptrCtrl_Alt_a)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_a>::press = (Ctrl_Shift_a::ptrCtrl_Shift_a)();
template<> cogui::key& cogui::on_impl<Alt_Shift_a>::press = (Alt_Shift_a::ptrAlt_Shift_a)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_a>::press = (Ctrl_Alt_Shift_a::ptrCtrl_Alt_Shift_a)();

// Key B
template<> cogui::key& cogui::on_impl<NoMod_b>::press = (NoMod_b::ptrNoMod_b)();
template<> cogui::key& cogui::on_impl<Shift_b>::press = (Shift_b::ptrShift_b)();
template<> cogui::key& cogui::on_impl<Ctrl_b>::press = (Ctrl_b::ptrCtrl_b)();
template<> cogui::key& cogui::on_impl<Alt_b>::press = (Alt_b::ptrAlt_b)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_b>::press = (Ctrl_Alt_b::ptrCtrl_Alt_b)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_b>::press = (Ctrl_Shift_b::ptrCtrl_Shift_b)();
template<> cogui::key& cogui::on_impl<Alt_Shift_b>::press = (Alt_Shift_b::ptrAlt_Shift_b)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_b>::press = (Ctrl_Alt_Shift_b::ptrCtrl_Alt_Shift_b)();

// Key C
template<> cogui::key& cogui::on_impl<NoMod_c>::press = (NoMod_c::ptrNoMod_c)();
template<> cogui::key& cogui::on_impl<Shift_c>::press = (Shift_c::ptrShift_c)();
template<> cogui::key& cogui::on_impl<Ctrl_c>::press = (Ctrl_c::ptrCtrl_c)();
template<> cogui::key& cogui::on_impl<Alt_c>::press = (Alt_c::ptrAlt_c)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_c>::press = (Ctrl_Alt_c::ptrCtrl_Alt_c)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_c>::press = (Ctrl_Shift_c::ptrCtrl_Shift_c)();
template<> cogui::key& cogui::on_impl<Alt_Shift_c>::press = (Alt_Shift_c::ptrAlt_Shift_c)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_c>::press = (Ctrl_Alt_Shift_c::ptrCtrl_Alt_Shift_c)();

// Key D
template<> cogui::key& cogui::on_impl<NoMod_d>::press = (NoMod_d::ptrNoMod_d)();
template<> cogui::key& cogui::on_impl<Shift_d>::press = (Shift_d::ptrShift_d)();
template<> cogui::key& cogui::on_impl<Ctrl_d>::press = (Ctrl_d::ptrCtrl_d)();
template<> cogui::key& cogui::on_impl<Alt_d>::press = (Alt_d::ptrAlt_d)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_d>::press = (Ctrl_Alt_d::ptrCtrl_Alt_d)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_d>::press = (Ctrl_Shift_d::ptrCtrl_Shift_d)();
template<> cogui::key& cogui::on_impl<Alt_Shift_d>::press = (Alt_Shift_d::ptrAlt_Shift_d)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_d>::press = (Ctrl_Alt_Shift_d::ptrCtrl_Alt_Shift_d)();

// Key E
template<> cogui::key& cogui::on_impl<NoMod_e>::press = (NoMod_e::ptrNoMod_e)();
template<> cogui::key& cogui::on_impl<Shift_e>::press = (Shift_e::ptrShift_e)();
template<> cogui::key& cogui::on_impl<Ctrl_e>::press = (Ctrl_e::ptrCtrl_e)();
template<> cogui::key& cogui::on_impl<Alt_e>::press = (Alt_e::ptrAlt_e)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_e>::press = (Ctrl_Alt_e::ptrCtrl_Alt_e)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_e>::press = (Ctrl_Shift_e::ptrCtrl_Shift_e)();
template<> cogui::key& cogui::on_impl<Alt_Shift_e>::press = (Alt_Shift_e::ptrAlt_Shift_e)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_e>::press = (Ctrl_Alt_Shift_e::ptrCtrl_Alt_Shift_e)();

// Key F
template<> cogui::key& cogui::on_impl<NoMod_f>::press = (NoMod_f::ptrNoMod_f)();
template<> cogui::key& cogui::on_impl<Shift_f>::press = (Shift_f::ptrShift_f)();
template<> cogui::key& cogui::on_impl<Ctrl_f>::press = (Ctrl_f::ptrCtrl_f)();
template<> cogui::key& cogui::on_impl<Alt_f>::press = (Alt_f::ptrAlt_f)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f>::press = (Ctrl_Alt_f::ptrCtrl_Alt_f)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f>::press = (Ctrl_Shift_f::ptrCtrl_Shift_f)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f>::press = (Alt_Shift_f::ptrAlt_Shift_f)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f>::press = (Ctrl_Alt_Shift_f::ptrCtrl_Alt_Shift_f)();

// Key G
template<> cogui::key& cogui::on_impl<NoMod_g>::press = (NoMod_g::ptrNoMod_g)();
template<> cogui::key& cogui::on_impl<Shift_g>::press = (Shift_g::ptrShift_g)();
template<> cogui::key& cogui::on_impl<Ctrl_g>::press = (Ctrl_g::ptrCtrl_g)();
template<> cogui::key& cogui::on_impl<Alt_g>::press = (Alt_g::ptrAlt_g)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_g>::press = (Ctrl_Alt_g::ptrCtrl_Alt_g)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_g>::press = (Ctrl_Shift_g::ptrCtrl_Shift_g)();
template<> cogui::key& cogui::on_impl<Alt_Shift_g>::press = (Alt_Shift_g::ptrAlt_Shift_g)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_g>::press = (Ctrl_Alt_Shift_g::ptrCtrl_Alt_Shift_g)();

// Key H
template<> cogui::key& cogui::on_impl<NoMod_h>::press = (NoMod_h::ptrNoMod_h)();
template<> cogui::key& cogui::on_impl<Shift_h>::press = (Shift_h::ptrShift_h)();
template<> cogui::key& cogui::on_impl<Ctrl_h>::press = (Ctrl_h::ptrCtrl_h)();
template<> cogui::key& cogui::on_impl<Alt_h>::press = (Alt_h::ptrAlt_h)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_h>::press = (Ctrl_Alt_h::ptrCtrl_Alt_h)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_h>::press = (Ctrl_Shift_h::ptrCtrl_Shift_h)();
template<> cogui::key& cogui::on_impl<Alt_Shift_h>::press = (Alt_Shift_h::ptrAlt_Shift_h)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_h>::press = (Ctrl_Alt_Shift_h::ptrCtrl_Alt_Shift_h)();

// Key I
template<> cogui::key& cogui::on_impl<NoMod_i>::press = (NoMod_i::ptrNoMod_i)();
template<> cogui::key& cogui::on_impl<Shift_i>::press = (Shift_i::ptrShift_i)();
template<> cogui::key& cogui::on_impl<Ctrl_i>::press = (Ctrl_i::ptrCtrl_i)();
template<> cogui::key& cogui::on_impl<Alt_i>::press = (Alt_i::ptrAlt_i)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_i>::press = (Ctrl_Alt_i::ptrCtrl_Alt_i)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_i>::press = (Ctrl_Shift_i::ptrCtrl_Shift_i)();
template<> cogui::key& cogui::on_impl<Alt_Shift_i>::press = (Alt_Shift_i::ptrAlt_Shift_i)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_i>::press = (Ctrl_Alt_Shift_i::ptrCtrl_Alt_Shift_i)();

// Key J
template<> cogui::key& cogui::on_impl<NoMod_j>::press = (NoMod_j::ptrNoMod_j)();
template<> cogui::key& cogui::on_impl<Shift_j>::press = (Shift_j::ptrShift_j)();
template<> cogui::key& cogui::on_impl<Ctrl_j>::press = (Ctrl_j::ptrCtrl_j)();
template<> cogui::key& cogui::on_impl<Alt_j>::press = (Alt_j::ptrAlt_j)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_j>::press = (Ctrl_Alt_j::ptrCtrl_Alt_j)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_j>::press = (Ctrl_Shift_j::ptrCtrl_Shift_j)();
template<> cogui::key& cogui::on_impl<Alt_Shift_j>::press = (Alt_Shift_j::ptrAlt_Shift_j)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_j>::press = (Ctrl_Alt_Shift_j::ptrCtrl_Alt_Shift_j)();

// Key K
template<> cogui::key& cogui::on_impl<NoMod_k>::press = (NoMod_k::ptrNoMod_k)();
template<> cogui::key& cogui::on_impl<Shift_k>::press = (Shift_k::ptrShift_k)();
template<> cogui::key& cogui::on_impl<Ctrl_k>::press = (Ctrl_k::ptrCtrl_k)();
template<> cogui::key& cogui::on_impl<Alt_k>::press = (Alt_k::ptrAlt_k)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_k>::press = (Ctrl_Alt_k::ptrCtrl_Alt_k)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_k>::press = (Ctrl_Shift_k::ptrCtrl_Shift_k)();
template<> cogui::key& cogui::on_impl<Alt_Shift_k>::press = (Alt_Shift_k::ptrAlt_Shift_k)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_k>::press = (Ctrl_Alt_Shift_k::ptrCtrl_Alt_Shift_k)();

// Key L
template<> cogui::key& cogui::on_impl<NoMod_l>::press = (NoMod_l::ptrNoMod_l)();
template<> cogui::key& cogui::on_impl<Shift_l>::press = (Shift_l::ptrShift_l)();
template<> cogui::key& cogui::on_impl<Ctrl_l>::press = (Ctrl_l::ptrCtrl_l)();
template<> cogui::key& cogui::on_impl<Alt_l>::press = (Alt_l::ptrAlt_l)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_l>::press = (Ctrl_Alt_l::ptrCtrl_Alt_l)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_l>::press = (Ctrl_Shift_l::ptrCtrl_Shift_l)();
template<> cogui::key& cogui::on_impl<Alt_Shift_l>::press = (Alt_Shift_l::ptrAlt_Shift_l)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_l>::press = (Ctrl_Alt_Shift_l::ptrCtrl_Alt_Shift_l)();

// Key M
template<> cogui::key& cogui::on_impl<NoMod_m>::press = (NoMod_m::ptrNoMod_m)();
template<> cogui::key& cogui::on_impl<Shift_m>::press = (Shift_m::ptrShift_m)();
template<> cogui::key& cogui::on_impl<Ctrl_m>::press = (Ctrl_m::ptrCtrl_m)();
template<> cogui::key& cogui::on_impl<Alt_m>::press = (Alt_m::ptrAlt_m)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_m>::press = (Ctrl_Alt_m::ptrCtrl_Alt_m)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_m>::press = (Ctrl_Shift_m::ptrCtrl_Shift_m)();
template<> cogui::key& cogui::on_impl<Alt_Shift_m>::press = (Alt_Shift_m::ptrAlt_Shift_m)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_m>::press = (Ctrl_Alt_Shift_m::ptrCtrl_Alt_Shift_m)();

// Key N
template<> cogui::key& cogui::on_impl<NoMod_n>::press = (NoMod_n::ptrNoMod_n)();
template<> cogui::key& cogui::on_impl<Shift_n>::press = (Shift_n::ptrShift_n)();
template<> cogui::key& cogui::on_impl<Ctrl_n>::press = (Ctrl_n::ptrCtrl_n)();
template<> cogui::key& cogui::on_impl<Alt_n>::press = (Alt_n::ptrAlt_n)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_n>::press = (Ctrl_Alt_n::ptrCtrl_Alt_n)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_n>::press = (Ctrl_Shift_n::ptrCtrl_Shift_n)();
template<> cogui::key& cogui::on_impl<Alt_Shift_n>::press = (Alt_Shift_n::ptrAlt_Shift_n)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_n>::press = (Ctrl_Alt_Shift_n::ptrCtrl_Alt_Shift_n)();

// Key O
template<> cogui::key& cogui::on_impl<NoMod_o>::press = (NoMod_o::ptrNoMod_o)();
template<> cogui::key& cogui::on_impl<Shift_o>::press = (Shift_o::ptrShift_o)();
template<> cogui::key& cogui::on_impl<Ctrl_o>::press = (Ctrl_o::ptrCtrl_o)();
template<> cogui::key& cogui::on_impl<Alt_o>::press = (Alt_o::ptrAlt_o)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_o>::press = (Ctrl_Alt_o::ptrCtrl_Alt_o)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_o>::press = (Ctrl_Shift_o::ptrCtrl_Shift_o)();
template<> cogui::key& cogui::on_impl<Alt_Shift_o>::press = (Alt_Shift_o::ptrAlt_Shift_o)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_o>::press = (Ctrl_Alt_Shift_o::ptrCtrl_Alt_Shift_o)();

// Key P
template<> cogui::key& cogui::on_impl<NoMod_p>::press = (NoMod_p::ptrNoMod_p)();
template<> cogui::key& cogui::on_impl<Shift_p>::press = (Shift_p::ptrShift_p)();
template<> cogui::key& cogui::on_impl<Ctrl_p>::press = (Ctrl_p::ptrCtrl_p)();
template<> cogui::key& cogui::on_impl<Alt_p>::press = (Alt_p::ptrAlt_p)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_p>::press = (Ctrl_Alt_p::ptrCtrl_Alt_p)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_p>::press = (Ctrl_Shift_p::ptrCtrl_Shift_p)();
template<> cogui::key& cogui::on_impl<Alt_Shift_p>::press = (Alt_Shift_p::ptrAlt_Shift_p)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_p>::press = (Ctrl_Alt_Shift_p::ptrCtrl_Alt_Shift_p)();

// Key Q
template<> cogui::key& cogui::on_impl<NoMod_q>::press = (NoMod_q::ptrNoMod_q)();
template<> cogui::key& cogui::on_impl<Shift_q>::press = (Shift_q::ptrShift_q)();
template<> cogui::key& cogui::on_impl<Ctrl_q>::press = (Ctrl_q::ptrCtrl_q)();
template<> cogui::key& cogui::on_impl<Alt_q>::press = (Alt_q::ptrAlt_q)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_q>::press = (Ctrl_Alt_q::ptrCtrl_Alt_q)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_q>::press = (Ctrl_Shift_q::ptrCtrl_Shift_q)();
template<> cogui::key& cogui::on_impl<Alt_Shift_q>::press = (Alt_Shift_q::ptrAlt_Shift_q)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_q>::press = (Ctrl_Alt_Shift_q::ptrCtrl_Alt_Shift_q)();

// Key R
template<> cogui::key& cogui::on_impl<NoMod_r>::press = (NoMod_r::ptrNoMod_r)();
template<> cogui::key& cogui::on_impl<Shift_r>::press = (Shift_r::ptrShift_r)();
template<> cogui::key& cogui::on_impl<Ctrl_r>::press = (Ctrl_r::ptrCtrl_r)();
template<> cogui::key& cogui::on_impl<Alt_r>::press = (Alt_r::ptrAlt_r)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_r>::press = (Ctrl_Alt_r::ptrCtrl_Alt_r)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_r>::press = (Ctrl_Shift_r::ptrCtrl_Shift_r)();
template<> cogui::key& cogui::on_impl<Alt_Shift_r>::press = (Alt_Shift_r::ptrAlt_Shift_r)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_r>::press = (Ctrl_Alt_Shift_r::ptrCtrl_Alt_Shift_r)();

// Key S
template<> cogui::key& cogui::on_impl<NoMod_s>::press = (NoMod_s::ptrNoMod_s)();
template<> cogui::key& cogui::on_impl<Shift_s>::press = (Shift_s::ptrShift_s)();
template<> cogui::key& cogui::on_impl<Ctrl_s>::press = (Ctrl_s::ptrCtrl_s)();
template<> cogui::key& cogui::on_impl<Alt_s>::press = (Alt_s::ptrAlt_s)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_s>::press = (Ctrl_Alt_s::ptrCtrl_Alt_s)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_s>::press = (Ctrl_Shift_s::ptrCtrl_Shift_s)();
template<> cogui::key& cogui::on_impl<Alt_Shift_s>::press = (Alt_Shift_s::ptrAlt_Shift_s)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_s>::press = (Ctrl_Alt_Shift_s::ptrCtrl_Alt_Shift_s)();

// Key T
template<> cogui::key& cogui::on_impl<NoMod_t>::press = (NoMod_t::ptrNoMod_t)();
template<> cogui::key& cogui::on_impl<Shift_t>::press = (Shift_t::ptrShift_t)();
template<> cogui::key& cogui::on_impl<Ctrl_t>::press = (Ctrl_t::ptrCtrl_t)();
template<> cogui::key& cogui::on_impl<Alt_t>::press = (Alt_t::ptrAlt_t)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_t>::press = (Ctrl_Alt_t::ptrCtrl_Alt_t)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_t>::press = (Ctrl_Shift_t::ptrCtrl_Shift_t)();
template<> cogui::key& cogui::on_impl<Alt_Shift_t>::press = (Alt_Shift_t::ptrAlt_Shift_t)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_t>::press = (Ctrl_Alt_Shift_t::ptrCtrl_Alt_Shift_t)();

// Key U
template<> cogui::key& cogui::on_impl<NoMod_u>::press = (NoMod_u::ptrNoMod_u)();
template<> cogui::key& cogui::on_impl<Shift_u>::press = (Shift_u::ptrShift_u)();
template<> cogui::key& cogui::on_impl<Ctrl_u>::press = (Ctrl_u::ptrCtrl_u)();
template<> cogui::key& cogui::on_impl<Alt_u>::press = (Alt_u::ptrAlt_u)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_u>::press = (Ctrl_Alt_u::ptrCtrl_Alt_u)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_u>::press = (Ctrl_Shift_u::ptrCtrl_Shift_u)();
template<> cogui::key& cogui::on_impl<Alt_Shift_u>::press = (Alt_Shift_u::ptrAlt_Shift_u)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_u>::press = (Ctrl_Alt_Shift_u::ptrCtrl_Alt_Shift_u)();

// Key V
template<> cogui::key& cogui::on_impl<NoMod_v>::press = (NoMod_v::ptrNoMod_v)();
template<> cogui::key& cogui::on_impl<Shift_v>::press = (Shift_v::ptrShift_v)();
template<> cogui::key& cogui::on_impl<Ctrl_v>::press = (Ctrl_v::ptrCtrl_v)();
template<> cogui::key& cogui::on_impl<Alt_v>::press = (Alt_v::ptrAlt_v)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_v>::press = (Ctrl_Alt_v::ptrCtrl_Alt_v)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_v>::press = (Ctrl_Shift_v::ptrCtrl_Shift_v)();
template<> cogui::key& cogui::on_impl<Alt_Shift_v>::press = (Alt_Shift_v::ptrAlt_Shift_v)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_v>::press = (Ctrl_Alt_Shift_v::ptrCtrl_Alt_Shift_v)();

// Key W
template<> cogui::key& cogui::on_impl<NoMod_w>::press = (NoMod_w::ptrNoMod_w)();
template<> cogui::key& cogui::on_impl<Shift_w>::press = (Shift_w::ptrShift_w)();
template<> cogui::key& cogui::on_impl<Ctrl_w>::press = (Ctrl_w::ptrCtrl_w)();
template<> cogui::key& cogui::on_impl<Alt_w>::press = (Alt_w::ptrAlt_w)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_w>::press = (Ctrl_Alt_w::ptrCtrl_Alt_w)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_w>::press = (Ctrl_Shift_w::ptrCtrl_Shift_w)();
template<> cogui::key& cogui::on_impl<Alt_Shift_w>::press = (Alt_Shift_w::ptrAlt_Shift_w)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_w>::press = (Ctrl_Alt_Shift_w::ptrCtrl_Alt_Shift_w)();

// Key X
template<> cogui::key& cogui::on_impl<NoMod_x>::press = (NoMod_x::ptrNoMod_x)();
template<> cogui::key& cogui::on_impl<Shift_x>::press = (Shift_x::ptrShift_x)();
template<> cogui::key& cogui::on_impl<Ctrl_x>::press = (Ctrl_x::ptrCtrl_x)();
template<> cogui::key& cogui::on_impl<Alt_x>::press = (Alt_x::ptrAlt_x)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_x>::press = (Ctrl_Alt_x::ptrCtrl_Alt_x)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_x>::press = (Ctrl_Shift_x::ptrCtrl_Shift_x)();
template<> cogui::key& cogui::on_impl<Alt_Shift_x>::press = (Alt_Shift_x::ptrAlt_Shift_x)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_x>::press = (Ctrl_Alt_Shift_x::ptrCtrl_Alt_Shift_x)();

// Key Y
template<> cogui::key& cogui::on_impl<NoMod_y>::press = (NoMod_y::ptrNoMod_y)();
template<> cogui::key& cogui::on_impl<Shift_y>::press = (Shift_y::ptrShift_y)();
template<> cogui::key& cogui::on_impl<Ctrl_y>::press = (Ctrl_y::ptrCtrl_y)();
template<> cogui::key& cogui::on_impl<Alt_y>::press = (Alt_y::ptrAlt_y)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_y>::press = (Ctrl_Alt_y::ptrCtrl_Alt_y)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_y>::press = (Ctrl_Shift_y::ptrCtrl_Shift_y)();
template<> cogui::key& cogui::on_impl<Alt_Shift_y>::press = (Alt_Shift_y::ptrAlt_Shift_y)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_y>::press = (Ctrl_Alt_Shift_y::ptrCtrl_Alt_Shift_y)();

// Key Z
template<> cogui::key& cogui::on_impl<NoMod_z>::press = (NoMod_z::ptrNoMod_z)();
template<> cogui::key& cogui::on_impl<Shift_z>::press = (Shift_z::ptrShift_z)();
template<> cogui::key& cogui::on_impl<Ctrl_z>::press = (Ctrl_z::ptrCtrl_z)();
template<> cogui::key& cogui::on_impl<Alt_z>::press = (Alt_z::ptrAlt_z)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_z>::press = (Ctrl_Alt_z::ptrCtrl_Alt_z)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_z>::press = (Ctrl_Shift_z::ptrCtrl_Shift_z)();
template<> cogui::key& cogui::on_impl<Alt_Shift_z>::press = (Alt_Shift_z::ptrAlt_Shift_z)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_z>::press = (Ctrl_Alt_Shift_z::ptrCtrl_Alt_Shift_z)();

// Function Keys (F1 to F12)
template<> cogui::key& cogui::on_impl<NoMod_f1>::press = (NoMod_f1::ptrNoMod_f1)();
template<> cogui::key& cogui::on_impl<Shift_f1>::press = (Shift_f1::ptrShift_f1)();
template<> cogui::key& cogui::on_impl<Ctrl_f1>::press = (Ctrl_f1::ptrCtrl_f1)();
template<> cogui::key& cogui::on_impl<Alt_f1>::press = (Alt_f1::ptrAlt_f1)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f1>::press = (Ctrl_Alt_f1::ptrCtrl_Alt_f1)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f1>::press = (Ctrl_Shift_f1::ptrCtrl_Shift_f1)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f1>::press = (Alt_Shift_f1::ptrAlt_Shift_f1)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f1>::press = (Ctrl_Alt_Shift_f1::ptrCtrl_Alt_Shift_f1)();

template<> cogui::key& cogui::on_impl<NoMod_f2>::press = (NoMod_f2::ptrNoMod_f2)();
template<> cogui::key& cogui::on_impl<Shift_f2>::press = (Shift_f2::ptrShift_f2)();
template<> cogui::key& cogui::on_impl<Ctrl_f2>::press = (Ctrl_f2::ptrCtrl_f2)();
template<> cogui::key& cogui::on_impl<Alt_f2>::press = (Alt_f2::ptrAlt_f2)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f2>::press = (Ctrl_Alt_f2::ptrCtrl_Alt_f2)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f2>::press = (Ctrl_Shift_f2::ptrCtrl_Shift_f2)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f2>::press = (Alt_Shift_f2::ptrAlt_Shift_f2)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f2>::press = (Ctrl_Alt_Shift_f2::ptrCtrl_Alt_Shift_f2)();

template<> cogui::key& cogui::on_impl<NoMod_f3>::press = (NoMod_f3::ptrNoMod_f3)();
template<> cogui::key& cogui::on_impl<Shift_f3>::press = (Shift_f3::ptrShift_f3)();
template<> cogui::key& cogui::on_impl<Ctrl_f3>::press = (Ctrl_f3::ptrCtrl_f3)();
template<> cogui::key& cogui::on_impl<Alt_f3>::press = (Alt_f3::ptrAlt_f3)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f3>::press = (Ctrl_Alt_f3::ptrCtrl_Alt_f3)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f3>::press = (Ctrl_Shift_f3::ptrCtrl_Shift_f3)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f3>::press = (Alt_Shift_f3::ptrAlt_Shift_f3)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f3>::press = (Ctrl_Alt_Shift_f3::ptrCtrl_Alt_Shift_f3)();

template<> cogui::key& cogui::on_impl<NoMod_f4>::press = (NoMod_f4::ptrNoMod_f4)();
template<> cogui::key& cogui::on_impl<Shift_f4>::press = (Shift_f4::ptrShift_f4)();
template<> cogui::key& cogui::on_impl<Ctrl_f4>::press = (Ctrl_f4::ptrCtrl_f4)();
template<> cogui::key& cogui::on_impl<Alt_f4>::press = (Alt_f4::ptrAlt_f4)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f4>::press = (Ctrl_Alt_f4::ptrCtrl_Alt_f4)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f4>::press = (Ctrl_Shift_f4::ptrCtrl_Shift_f4)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f4>::press = (Alt_Shift_f4::ptrAlt_Shift_f4)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f4>::press = (Ctrl_Alt_Shift_f4::ptrCtrl_Alt_Shift_f4)();

template<> cogui::key& cogui::on_impl<NoMod_f5>::press = (NoMod_f5::ptrNoMod_f5)();
template<> cogui::key& cogui::on_impl<Shift_f5>::press = (Shift_f5::ptrShift_f5)();
template<> cogui::key& cogui::on_impl<Ctrl_f5>::press = (Ctrl_f5::ptrCtrl_f5)();
template<> cogui::key& cogui::on_impl<Alt_f5>::press = (Alt_f5::ptrAlt_f5)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f5>::press = (Ctrl_Alt_f5::ptrCtrl_Alt_f5)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f5>::press = (Ctrl_Shift_f5::ptrCtrl_Shift_f5)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f5>::press = (Alt_Shift_f5::ptrAlt_Shift_f5)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f5>::press = (Ctrl_Alt_Shift_f5::ptrCtrl_Alt_Shift_f5)();

template<> cogui::key& cogui::on_impl<NoMod_f6>::press = (NoMod_f6::ptrNoMod_f6)();
template<> cogui::key& cogui::on_impl<Shift_f6>::press = (Shift_f6::ptrShift_f6)();
template<> cogui::key& cogui::on_impl<Ctrl_f6>::press = (Ctrl_f6::ptrCtrl_f6)();
template<> cogui::key& cogui::on_impl<Alt_f6>::press = (Alt_f6::ptrAlt_f6)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f6>::press = (Ctrl_Alt_f6::ptrCtrl_Alt_f6)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f6>::press = (Ctrl_Shift_f6::ptrCtrl_Shift_f6)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f6>::press = (Alt_Shift_f6::ptrAlt_Shift_f6)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f6>::press = (Ctrl_Alt_Shift_f6::ptrCtrl_Alt_Shift_f6)();

template<> cogui::key& cogui::on_impl<NoMod_f7>::press = (NoMod_f7::ptrNoMod_f7)();
template<> cogui::key& cogui::on_impl<Shift_f7>::press = (Shift_f7::ptrShift_f7)();
template<> cogui::key& cogui::on_impl<Ctrl_f7>::press = (Ctrl_f7::ptrCtrl_f7)();
template<> cogui::key& cogui::on_impl<Alt_f7>::press = (Alt_f7::ptrAlt_f7)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f7>::press = (Ctrl_Alt_f7::ptrCtrl_Alt_f7)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f7>::press = (Ctrl_Shift_f7::ptrCtrl_Shift_f7)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f7>::press = (Alt_Shift_f7::ptrAlt_Shift_f7)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f7>::press = (Ctrl_Alt_Shift_f7::ptrCtrl_Alt_Shift_f7)();

template<> cogui::key& cogui::on_impl<NoMod_f8>::press = (NoMod_f8::ptrNoMod_f8)();
template<> cogui::key& cogui::on_impl<Shift_f8>::press = (Shift_f8::ptrShift_f8)();
template<> cogui::key& cogui::on_impl<Ctrl_f8>::press = (Ctrl_f8::ptrCtrl_f8)();
template<> cogui::key& cogui::on_impl<Alt_f8>::press = (Alt_f8::ptrAlt_f8)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f8>::press = (Ctrl_Alt_f8::ptrCtrl_Alt_f8)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f8>::press = (Ctrl_Shift_f8::ptrCtrl_Shift_f8)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f8>::press = (Alt_Shift_f8::ptrAlt_Shift_f8)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f8>::press = (Ctrl_Alt_Shift_f8::ptrCtrl_Alt_Shift_f8)();

template<> cogui::key& cogui::on_impl<NoMod_f9>::press = (NoMod_f9::ptrNoMod_f9)();
template<> cogui::key& cogui::on_impl<Shift_f9>::press = (Shift_f9::ptrShift_f9)();
template<> cogui::key& cogui::on_impl<Ctrl_f9>::press = (Ctrl_f9::ptrCtrl_f9)();
template<> cogui::key& cogui::on_impl<Alt_f9>::press = (Alt_f9::ptrAlt_f9)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f9>::press = (Ctrl_Alt_f9::ptrCtrl_Alt_f9)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f9>::press = (Ctrl_Shift_f9::ptrCtrl_Shift_f9)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f9>::press = (Alt_Shift_f9::ptrAlt_Shift_f9)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f9>::press = (Ctrl_Alt_Shift_f9::ptrCtrl_Alt_Shift_f9)();

template<> cogui::key& cogui::on_impl<NoMod_f10>::press = (NoMod_f10::ptrNoMod_f10)();
template<> cogui::key& cogui::on_impl<Shift_f10>::press = (Shift_f10::ptrShift_f10)();
template<> cogui::key& cogui::on_impl<Ctrl_f10>::press = (Ctrl_f10::ptrCtrl_f10)();
template<> cogui::key& cogui::on_impl<Alt_f10>::press = (Alt_f10::ptrAlt_f10)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f10>::press = (Ctrl_Alt_f10::ptrCtrl_Alt_f10)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f10>::press = (Ctrl_Shift_f10::ptrCtrl_Shift_f10)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f10>::press = (Alt_Shift_f10::ptrAlt_Shift_f10)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f10>::press = (Ctrl_Alt_Shift_f10::ptrCtrl_Alt_Shift_f10)();

template<> cogui::key& cogui::on_impl<NoMod_f11>::press = (NoMod_f11::ptrNoMod_f11)();
template<> cogui::key& cogui::on_impl<Shift_f11>::press = (Shift_f11::ptrShift_f11)();
template<> cogui::key& cogui::on_impl<Ctrl_f11>::press = (Ctrl_f11::ptrCtrl_f11)();
template<> cogui::key& cogui::on_impl<Alt_f11>::press = (Alt_f11::ptrAlt_f11)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f11>::press = (Ctrl_Alt_f11::ptrCtrl_Alt_f11)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f11>::press = (Ctrl_Shift_f11::ptrCtrl_Shift_f11)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f11>::press = (Alt_Shift_f11::ptrAlt_Shift_f11)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f11>::press = (Ctrl_Alt_Shift_f11::ptrCtrl_Alt_Shift_f11)();

template<> cogui::key& cogui::on_impl<NoMod_f12>::press = (NoMod_f12::ptrNoMod_f12)();
template<> cogui::key& cogui::on_impl<Shift_f12>::press = (Shift_f12::ptrShift_f12)();
template<> cogui::key& cogui::on_impl<Ctrl_f12>::press = (Ctrl_f12::ptrCtrl_f12)();
template<> cogui::key& cogui::on_impl<Alt_f12>::press = (Alt_f12::ptrAlt_f12)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_f12>::press = (Ctrl_Alt_f12::ptrCtrl_Alt_f12)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_f12>::press = (Ctrl_Shift_f12::ptrCtrl_Shift_f12)();
template<> cogui::key& cogui::on_impl<Alt_Shift_f12>::press = (Alt_Shift_f12::ptrAlt_Shift_f12)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_f12>::press = (Ctrl_Alt_Shift_f12::ptrCtrl_Alt_Shift_f12)();

// Arrow Keys
template<> cogui::key& cogui::on_impl<NoMod_up>::press = (NoMod_up::ptrNoMod_up)();
template<> cogui::key& cogui::on_impl<Shift_up>::press = (Shift_up::ptrShift_up)();
template<> cogui::key& cogui::on_impl<Ctrl_up>::press = (Ctrl_up::ptrCtrl_up)();
template<> cogui::key& cogui::on_impl<Alt_up>::press = (Alt_up::ptrAlt_up)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_up>::press = (Ctrl_Alt_up::ptrCtrl_Alt_up)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_up>::press = (Ctrl_Shift_up::ptrCtrl_Shift_up)();
template<> cogui::key& cogui::on_impl<Alt_Shift_up>::press = (Alt_Shift_up::ptrAlt_Shift_up)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_up>::press = (Ctrl_Alt_Shift_up::ptrCtrl_Alt_Shift_up)();

template<> cogui::key& cogui::on_impl<NoMod_down>::press = (NoMod_down::ptrNoMod_down)();
template<> cogui::key& cogui::on_impl<Shift_down>::press = (Shift_down::ptrShift_down)();
template<> cogui::key& cogui::on_impl<Ctrl_down>::press = (Ctrl_down::ptrCtrl_down)();
template<> cogui::key& cogui::on_impl<Alt_down>::press = (Alt_down::ptrAlt_down)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_down>::press = (Ctrl_Alt_down::ptrCtrl_Alt_down)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_down>::press = (Ctrl_Shift_down::ptrCtrl_Shift_down)();
template<> cogui::key& cogui::on_impl<Alt_Shift_down>::press = (Alt_Shift_down::ptrAlt_Shift_down)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_down>::press = (Ctrl_Alt_Shift_down::ptrCtrl_Alt_Shift_down)();

template<> cogui::key& cogui::on_impl<NoMod_left>::press = (NoMod_left::ptrNoMod_left)();
template<> cogui::key& cogui::on_impl<Shift_left>::press = (Shift_left::ptrShift_left)();
template<> cogui::key& cogui::on_impl<Ctrl_left>::press = (Ctrl_left::ptrCtrl_left)();
template<> cogui::key& cogui::on_impl<Alt_left>::press = (Alt_left::ptrAlt_left)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_left>::press = (Ctrl_Alt_left::ptrCtrl_Alt_left)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_left>::press = (Ctrl_Shift_left::ptrCtrl_Shift_left)();
template<> cogui::key& cogui::on_impl<Alt_Shift_left>::press = (Alt_Shift_left::ptrAlt_Shift_left)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_left>::press = (Ctrl_Alt_Shift_left::ptrCtrl_Alt_Shift_left)();

template<> cogui::key& cogui::on_impl<NoMod_right>::press = (NoMod_right::ptrNoMod_right)();
template<> cogui::key& cogui::on_impl<Shift_right>::press = (Shift_right::ptrShift_right)();
template<> cogui::key& cogui::on_impl<Ctrl_right>::press = (Ctrl_right::ptrCtrl_right)();
template<> cogui::key& cogui::on_impl<Alt_right>::press = (Alt_right::ptrAlt_right)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_right>::press = (Ctrl_Alt_right::ptrCtrl_Alt_right)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_right>::press = (Ctrl_Shift_right::ptrCtrl_Shift_right)();
template<> cogui::key& cogui::on_impl<Alt_Shift_right>::press = (Alt_Shift_right::ptrAlt_Shift_right)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_right>::press = (Ctrl_Alt_Shift_right::ptrCtrl_Alt_Shift_right)();

// Number Keys (0-9)
template<> cogui::key& cogui::on_impl<NoMod_0>::press = (NoMod_0::ptrNoMod_0)();
template<> cogui::key& cogui::on_impl<Shift_0>::press = (Shift_0::ptrShift_0)();
template<> cogui::key& cogui::on_impl<Ctrl_0>::press = (Ctrl_0::ptrCtrl_0)();
template<> cogui::key& cogui::on_impl<Alt_0>::press = (Alt_0::ptrAlt_0)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_0>::press = (Ctrl_Alt_0::ptrCtrl_Alt_0)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_0>::press = (Ctrl_Shift_0::ptrCtrl_Shift_0)();
template<> cogui::key& cogui::on_impl<Alt_Shift_0>::press = (Alt_Shift_0::ptrAlt_Shift_0)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_0>::press = (Ctrl_Alt_Shift_0::ptrCtrl_Alt_Shift_0)();

template<> cogui::key& cogui::on_impl<NoMod_1>::press = (NoMod_1::ptrNoMod_1)();
template<> cogui::key& cogui::on_impl<Shift_1>::press = (Shift_1::ptrShift_1)();
template<> cogui::key& cogui::on_impl<Ctrl_1>::press = (Ctrl_1::ptrCtrl_1)();
template<> cogui::key& cogui::on_impl<Alt_1>::press = (Alt_1::ptrAlt_1)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_1>::press = (Ctrl_Alt_1::ptrCtrl_Alt_1)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_1>::press = (Ctrl_Shift_1::ptrCtrl_Shift_1)();
template<> cogui::key& cogui::on_impl<Alt_Shift_1>::press = (Alt_Shift_1::ptrAlt_Shift_1)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_1>::press = (Ctrl_Alt_Shift_1::ptrCtrl_Alt_Shift_1)();

template<> cogui::key& cogui::on_impl<NoMod_2>::press = (NoMod_2::ptrNoMod_2)();
template<> cogui::key& cogui::on_impl<Shift_2>::press = (Shift_2::ptrShift_2)();
template<> cogui::key& cogui::on_impl<Ctrl_2>::press = (Ctrl_2::ptrCtrl_2)();
template<> cogui::key& cogui::on_impl<Alt_2>::press = (Alt_2::ptrAlt_2)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_2>::press = (Ctrl_Alt_2::ptrCtrl_Alt_2)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_2>::press = (Ctrl_Shift_2::ptrCtrl_Shift_2)();
template<> cogui::key& cogui::on_impl<Alt_Shift_2>::press = (Alt_Shift_2::ptrAlt_Shift_2)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_2>::press = (Ctrl_Alt_Shift_2::ptrCtrl_Alt_Shift_2)();

template<> cogui::key& cogui::on_impl<NoMod_3>::press = (NoMod_3::ptrNoMod_3)();
template<> cogui::key& cogui::on_impl<Shift_3>::press = (Shift_3::ptrShift_3)();
template<> cogui::key& cogui::on_impl<Ctrl_3>::press = (Ctrl_3::ptrCtrl_3)();
template<> cogui::key& cogui::on_impl<Alt_3>::press = (Alt_3::ptrAlt_3)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_3>::press = (Ctrl_Alt_3::ptrCtrl_Alt_3)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_3>::press = (Ctrl_Shift_3::ptrCtrl_Shift_3)();
template<> cogui::key& cogui::on_impl<Alt_Shift_3>::press = (Alt_Shift_3::ptrAlt_Shift_3)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_3>::press = (Ctrl_Alt_Shift_3::ptrCtrl_Alt_Shift_3)();

template<> cogui::key& cogui::on_impl<NoMod_4>::press = (NoMod_4::ptrNoMod_4)();
template<> cogui::key& cogui::on_impl<Shift_4>::press = (Shift_4::ptrShift_4)();
template<> cogui::key& cogui::on_impl<Ctrl_4>::press = (Ctrl_4::ptrCtrl_4)();
template<> cogui::key& cogui::on_impl<Alt_4>::press = (Alt_4::ptrAlt_4)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_4>::press = (Ctrl_Alt_4::ptrCtrl_Alt_4)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_4>::press = (Ctrl_Shift_4::ptrCtrl_Shift_4)();
template<> cogui::key& cogui::on_impl<Alt_Shift_4>::press = (Alt_Shift_4::ptrAlt_Shift_4)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_4>::press = (Ctrl_Alt_Shift_4::ptrCtrl_Alt_Shift_4)();

template<> cogui::key& cogui::on_impl<NoMod_5>::press = (NoMod_5::ptrNoMod_5)();
template<> cogui::key& cogui::on_impl<Shift_5>::press = (Shift_5::ptrShift_5)();
template<> cogui::key& cogui::on_impl<Ctrl_5>::press = (Ctrl_5::ptrCtrl_5)();
template<> cogui::key& cogui::on_impl<Alt_5>::press = (Alt_5::ptrAlt_5)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_5>::press = (Ctrl_Alt_5::ptrCtrl_Alt_5)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_5>::press = (Ctrl_Shift_5::ptrCtrl_Shift_5)();
template<> cogui::key& cogui::on_impl<Alt_Shift_5>::press = (Alt_Shift_5::ptrAlt_Shift_5)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_5>::press = (Ctrl_Alt_Shift_5::ptrCtrl_Alt_Shift_5)();

template<> cogui::key& cogui::on_impl<NoMod_6>::press = (NoMod_6::ptrNoMod_6)();
template<> cogui::key& cogui::on_impl<Shift_6>::press = (Shift_6::ptrShift_6)();
template<> cogui::key& cogui::on_impl<Ctrl_6>::press = (Ctrl_6::ptrCtrl_6)();
template<> cogui::key& cogui::on_impl<Alt_6>::press = (Alt_6::ptrAlt_6)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_6>::press = (Ctrl_Alt_6::ptrCtrl_Alt_6)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_6>::press = (Ctrl_Shift_6::ptrCtrl_Shift_6)();
template<> cogui::key& cogui::on_impl<Alt_Shift_6>::press = (Alt_Shift_6::ptrAlt_Shift_6)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_6>::press = (Ctrl_Alt_Shift_6::ptrCtrl_Alt_Shift_6)();

template<> cogui::key& cogui::on_impl<NoMod_7>::press = (NoMod_7::ptrNoMod_7)();
template<> cogui::key& cogui::on_impl<Shift_7>::press = (Shift_7::ptrShift_7)();
template<> cogui::key& cogui::on_impl<Ctrl_7>::press = (Ctrl_7::ptrCtrl_7)();
template<> cogui::key& cogui::on_impl<Alt_7>::press = (Alt_7::ptrAlt_7)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_7>::press = (Ctrl_Alt_7::ptrCtrl_Alt_7)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_7>::press = (Ctrl_Shift_7::ptrCtrl_Shift_7)();
template<> cogui::key& cogui::on_impl<Alt_Shift_7>::press = (Alt_Shift_7::ptrAlt_Shift_7)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_7>::press = (Ctrl_Alt_Shift_7::ptrCtrl_Alt_Shift_7)();

template<> cogui::key& cogui::on_impl<NoMod_8>::press = (NoMod_8::ptrNoMod_8)();
template<> cogui::key& cogui::on_impl<Shift_8>::press = (Shift_8::ptrShift_8)();
template<> cogui::key& cogui::on_impl<Ctrl_8>::press = (Ctrl_8::ptrCtrl_8)();
template<> cogui::key& cogui::on_impl<Alt_8>::press = (Alt_8::ptrAlt_8)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_8>::press = (Ctrl_Alt_8::ptrCtrl_Alt_8)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_8>::press = (Ctrl_Shift_8::ptrCtrl_Shift_8)();
template<> cogui::key& cogui::on_impl<Alt_Shift_8>::press = (Alt_Shift_8::ptrAlt_Shift_8)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_8>::press = (Ctrl_Alt_Shift_8::ptrCtrl_Alt_Shift_8)();

template<> cogui::key& cogui::on_impl<NoMod_9>::press = (NoMod_9::ptrNoMod_9)();
template<> cogui::key& cogui::on_impl<Shift_9>::press = (Shift_9::ptrShift_9)();
template<> cogui::key& cogui::on_impl<Ctrl_9>::press = (Ctrl_9::ptrCtrl_9)();
template<> cogui::key& cogui::on_impl<Alt_9>::press = (Alt_9::ptrAlt_9)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_9>::press = (Ctrl_Alt_9::ptrCtrl_Alt_9)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_9>::press = (Ctrl_Shift_9::ptrCtrl_Shift_9)();
template<> cogui::key& cogui::on_impl<Alt_Shift_9>::press = (Alt_Shift_9::ptrAlt_Shift_9)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_9>::press = (Ctrl_Alt_Shift_9::ptrCtrl_Alt_Shift_9)();

template<> cogui::key& cogui::on_impl<NoMod_tab>::press = (NoMod_tab::ptrNoMod_tab)();
template<> cogui::key& cogui::on_impl<Shift_tab>::press = (Shift_tab::ptrShift_tab)();
template<> cogui::key& cogui::on_impl<Ctrl_tab>::press = (Ctrl_tab::ptrCtrl_tab)();
template<> cogui::key& cogui::on_impl<Alt_tab>::press = (Alt_tab::ptrAlt_tab)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_tab>::press = (Ctrl_Alt_tab::ptrCtrl_Alt_tab)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_tab>::press = (Ctrl_Shift_tab::ptrCtrl_Shift_tab)();
template<> cogui::key& cogui::on_impl<Alt_Shift_tab>::press = (Alt_Shift_tab::ptrAlt_Shift_tab)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_tab>::press = (Ctrl_Alt_Shift_tab::ptrCtrl_Alt_Shift_tab)();

template<> cogui::key& cogui::on_impl<NoMod_space>::press = (NoMod_space::ptrNoMod_space)();
template<> cogui::key& cogui::on_impl<Shift_space>::press = (Shift_space::ptrShift_space)();
template<> cogui::key& cogui::on_impl<Ctrl_space>::press = (Ctrl_space::ptrCtrl_space)();
template<> cogui::key& cogui::on_impl<Alt_space>::press = (Alt_space::ptrAlt_space)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_space>::press = (Ctrl_Alt_space::ptrCtrl_Alt_space)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_space>::press = (Ctrl_Shift_space::ptrCtrl_Shift_space)();
template<> cogui::key& cogui::on_impl<Alt_Shift_space>::press = (Alt_Shift_space::ptrAlt_Shift_space)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_space>::press = (Ctrl_Alt_Shift_space::ptrCtrl_Alt_Shift_space)();

template<> cogui::key& cogui::on_impl<NoMod_backspace>::press = (NoMod_backspace::ptrNoMod_backspace)();
template<> cogui::key& cogui::on_impl<Shift_backspace>::press = (Shift_backspace::ptrShift_backspace)();
template<> cogui::key& cogui::on_impl<Ctrl_backspace>::press = (Ctrl_backspace::ptrCtrl_backspace)();
template<> cogui::key& cogui::on_impl<Alt_backspace>::press = (Alt_backspace::ptrAlt_backspace)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_backspace>::press = (Ctrl_Alt_backspace::ptrCtrl_Alt_backspace)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_backspace>::press = (Ctrl_Shift_backspace::ptrCtrl_Shift_backspace)();
template<> cogui::key& cogui::on_impl<Alt_Shift_backspace>::press = (Alt_Shift_backspace::ptrAlt_Shift_backspace)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_backspace>::press = (Ctrl_Alt_Shift_backspace::ptrCtrl_Alt_Shift_backspace)();

template<> cogui::key& cogui::on_impl<NoMod_return>::press = (NoMod_return::ptrNoMod_return)();
template<> cogui::key& cogui::on_impl<Shift_return>::press = (Shift_return::ptrShift_return)();
template<> cogui::key& cogui::on_impl<Ctrl_return>::press = (Ctrl_return::ptrCtrl_return)();
template<> cogui::key& cogui::on_impl<Alt_return>::press = (Alt_return::ptrAlt_return)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_return>::press = (Ctrl_Alt_return::ptrCtrl_Alt_return)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_return>::press = (Ctrl_Shift_return::ptrCtrl_Shift_return)();
template<> cogui::key& cogui::on_impl<Alt_Shift_return>::press = (Alt_Shift_return::ptrAlt_Shift_return)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_return>::press = (Ctrl_Alt_Shift_return::ptrCtrl_Alt_Shift_return)();

template<> cogui::key& cogui::on_impl<NoMod_insert>::press = (NoMod_insert::ptrNoMod_insert)();
template<> cogui::key& cogui::on_impl<Shift_insert>::press = (Shift_insert::ptrShift_insert)();
template<> cogui::key& cogui::on_impl<Ctrl_insert>::press = (Ctrl_insert::ptrCtrl_insert)();
template<> cogui::key& cogui::on_impl<Alt_insert>::press = (Alt_insert::ptrAlt_insert)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_insert>::press = (Ctrl_Alt_insert::ptrCtrl_Alt_insert)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_insert>::press = (Ctrl_Shift_insert::ptrCtrl_Shift_insert)();
template<> cogui::key& cogui::on_impl<Alt_Shift_insert>::press = (Alt_Shift_insert::ptrAlt_Shift_insert)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_insert>::press = (Ctrl_Alt_Shift_insert::ptrCtrl_Alt_Shift_insert)();

template<> cogui::key& cogui::on_impl<NoMod_delete>::press = (NoMod_delete::ptrNoMod_delete)();
template<> cogui::key& cogui::on_impl<Shift_delete>::press = (Shift_delete::ptrShift_delete)();
template<> cogui::key& cogui::on_impl<Ctrl_delete>::press = (Ctrl_delete::ptrCtrl_delete)();
template<> cogui::key& cogui::on_impl<Alt_delete>::press = (Alt_delete::ptrAlt_delete)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_delete>::press = (Ctrl_Alt_delete::ptrCtrl_Alt_delete)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_delete>::press = (Ctrl_Shift_delete::ptrCtrl_Shift_delete)();
template<> cogui::key& cogui::on_impl<Alt_Shift_delete>::press = (Alt_Shift_delete::ptrAlt_Shift_delete)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_delete>::press = (Ctrl_Alt_Shift_delete::ptrCtrl_Alt_Shift_delete)();

template<> cogui::key& cogui::on_impl<NoMod_home>::press = (NoMod_home::ptrNoMod_home)();
template<> cogui::key& cogui::on_impl<Shift_home>::press = (Shift_home::ptrShift_home)();
template<> cogui::key& cogui::on_impl<Ctrl_home>::press = (Ctrl_home::ptrCtrl_home)();
template<> cogui::key& cogui::on_impl<Alt_home>::press = (Alt_home::ptrAlt_home)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_home>::press = (Ctrl_Alt_home::ptrCtrl_Alt_home)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_home>::press = (Ctrl_Shift_home::ptrCtrl_Shift_home)();
template<> cogui::key& cogui::on_impl<Alt_Shift_home>::press = (Alt_Shift_home::ptrAlt_Shift_home)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_home>::press = (Ctrl_Alt_Shift_home::ptrCtrl_Alt_Shift_home)();

template<> cogui::key& cogui::on_impl<NoMod_end>::press = (NoMod_end::ptrNoMod_end)();
template<> cogui::key& cogui::on_impl<Shift_end>::press = (Shift_end::ptrShift_end)();
template<> cogui::key& cogui::on_impl<Ctrl_end>::press = (Ctrl_end::ptrCtrl_end)();
template<> cogui::key& cogui::on_impl<Alt_end>::press = (Alt_end::ptrAlt_end)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_end>::press = (Ctrl_Alt_end::ptrCtrl_Alt_end)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_end>::press = (Ctrl_Shift_end::ptrCtrl_Shift_end)();
template<> cogui::key& cogui::on_impl<Alt_Shift_end>::press = (Alt_Shift_end::ptrAlt_Shift_end)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_end>::press = (Ctrl_Alt_Shift_end::ptrCtrl_Alt_Shift_end)();

template<> cogui::key& cogui::on_impl<NoMod_pgup>::press = (NoMod_pgup::ptrNoMod_pgup)();
template<> cogui::key& cogui::on_impl<Shift_pgup>::press = (Shift_pgup::ptrShift_pgup)();
template<> cogui::key& cogui::on_impl<Ctrl_pgup>::press = (Ctrl_pgup::ptrCtrl_pgup)();
template<> cogui::key& cogui::on_impl<Alt_pgup>::press = (Alt_pgup::ptrAlt_pgup)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_pgup>::press = (Ctrl_Alt_pgup::ptrCtrl_Alt_pgup)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_pgup>::press = (Ctrl_Shift_pgup::ptrCtrl_Shift_pgup)();
template<> cogui::key& cogui::on_impl<Alt_Shift_pgup>::press = (Alt_Shift_pgup::ptrAlt_Shift_pgup)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_pgup>::press = (Ctrl_Alt_Shift_pgup::ptrCtrl_Alt_Shift_pgup)();

template<> cogui::key& cogui::on_impl<NoMod_pgdn>::press = (NoMod_pgdn::ptrNoMod_pgdn)();
template<> cogui::key& cogui::on_impl<Shift_pgdn>::press = (Shift_pgdn::ptrShift_pgdn)();
template<> cogui::key& cogui::on_impl<Ctrl_pgdn>::press = (Ctrl_pgdn::ptrCtrl_pgdn)();
template<> cogui::key& cogui::on_impl<Alt_pgdn>::press = (Alt_pgdn::ptrAlt_pgdn)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_pgdn>::press = (Ctrl_Alt_pgdn::ptrCtrl_Alt_pgdn)();
template<> cogui::key& cogui::on_impl<Ctrl_Shift_pgdn>::press = (Ctrl_Shift_pgdn::ptrCtrl_Shift_pgdn)();
template<> cogui::key& cogui::on_impl<Alt_Shift_pgdn>::press = (Alt_Shift_pgdn::ptrAlt_Shift_pgdn)();
template<> cogui::key& cogui::on_impl<Ctrl_Alt_Shift_pgdn>::press = (Ctrl_Alt_Shift_pgdn::ptrCtrl_Alt_Shift_pgdn)();

}

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


namespace cogui {
cogui::key *abstract_hotkey_handler::get_key() const
{
    return k;
}

void abstract_hotkey_handler::set_key(cogui::key *newK)
{
    log_info() << "Setting a hotkey:" << newK->generator().get_chardata();
    k = newK;
}

}
