#ifndef MISO_H
#define MISO_H

#include <functional>
#include <memory>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>

#include "loguru.h"

namespace miso
{
template <class... Args> class signal;

namespace internal {

template<int ...> struct sequence {};
template<int N, int ...S> struct sequence_generator : sequence_generator<N - 1, N - 1, S...> {};
template<int ...S> struct sequence_generator<0, S...> { typedef sequence<S...> type; };

template<typename FT>
struct func_and_bool final {
    std::shared_ptr<FT> ft;
    bool active;
    void *addr;
    void* obj;
    void* sig_addr;
};

struct common_slot_base {
    virtual ~common_slot_base() = default;
};

template<class T, class FT, class SHT>
void connect_i(void* sig_addr, void* obj, T &&f, std::vector<common_slot_base *> &sholders, bool active = true, bool really_remove = false) {
    static SHT sh;
    func_and_bool<FT> fb{std::make_shared<FT>(std::forward<T>(f)), active, reinterpret_cast<void *>(&f), obj, sig_addr};
    bool already_in = false;

    info() << "looking for in:" << &f << " for obj:" << obj;
    std::for_each(sh.slots.begin(), sh.slots.end(),
                  [&](func_and_bool<FT> &s)
                    {
                        if (s.addr == fb.addr && s.obj == fb.obj && s.sig_addr == fb.sig_addr)
                        {
                            s.active = active; already_in = true;
                        }
                    }
    );

    if (!already_in && active && !really_remove)
    {
        sh.slots.emplace_back(fb);
    }

    if(already_in && really_remove)
    {
        sh.slots.erase(std::remove_if(sh.slots.begin(), sh.slots.end(),
                              [&](func_and_bool<FT> &s)
                                 {
                                     return (s.addr == fb.addr && s.obj == fb.obj && s.sig_addr == fb.sig_addr);
                                 }
        ), sh.slots.end());

    }

    if (std::find(sholders.begin(), sholders.end(), static_cast<common_slot_base *>(&sh)) == sholders.end())
    {
        sholders.push_back(&sh);
    }
}

template<class T>
struct emitter final {
    explicit emitter(const T &emtr) {
        sender_objs.push(&emtr);
        minstance = this;
    }

    ~emitter() {
        sender_objs.pop();
        minstance = nullptr;
    }

    static T *sender() {
        return const_cast<T *>(sender_objs.top());
    }

    static emitter<T> *instance() {
        return minstance;
    }

private:

    static std::stack<const T *> sender_objs;
    static emitter<T> *minstance;
};

template<class T> std::stack<const T *> emitter<T>::sender_objs;
template<class T> emitter<T> *emitter<T>::minstance = nullptr;

template<class T, class... Args>
emitter<T> &&operator <<(internal::emitter<T> &&e, signal<Args...> &s) {
    info() << "emitting: " << &s << " as " << s.name();
    s.delayed_dispatch( e.sender() );
    return std::forward<internal::emitter<T>>(e);
}
}

template <class... Args>
class signal final
{
    struct slot_holder_base : public internal::common_slot_base {
        virtual void run_slots(void*, void*, Args... args) = 0;
    };

    template<class T>
    struct slot_holder : public slot_holder_base {
        using FT = std::function<typename std::result_of<T(Args...)>::type(Args...)>;
        using slot_vec_type = std::vector<internal::func_and_bool<FT>>;
        slot_vec_type slots;

        void run_slots(void* sig_addr, void*sender_obj, Args... args) override {
            std::for_each(slots.begin(), slots.end(), [&](internal::func_and_bool<FT>& s)
            {
                info() << "trying: (s.obj) " << s.obj << "==" << sender_obj << " (sender_obj) and (s.sig_addr)" << s.sig_addr << "==" << sig_addr << " (sig_addr)";
                if (s.active && s.obj == sender_obj && s.sig_addr == sig_addr) (*(s.ft.get()))(args...);
            }
            );
        }
    };

    std::vector<internal::common_slot_base*> slot_holders;
    std::tuple<Args...> call_args;

    void emit_signal(void* sender_obj, Args... args) {
        for (auto& sh : slot_holders) {
            (dynamic_cast<slot_holder_base*>(sh))->run_slots(this, sender_obj, args...);
        }
    }

    template<int ...S>
    void delayed_call(void* sender_obj, internal::sequence<S...>)	{
        emit_signal(sender_obj, std::get<S>(call_args) ...);
    }

    void delayed_dispatch(void* sender_obj)	{
        delayed_call(sender_obj, typename internal::sequence_generator<sizeof...(Args)>::type());
    }

    std::string signal_name;

public:
    template<class T, class... Brgs> friend
    internal::emitter<T> && internal::operator <<(internal::emitter<T> &&e, signal<Brgs...> &s);

    explicit signal() = default;
    explicit signal(const char* n) : signal_name(n) {}

    ~signal() noexcept = default;

    template<class T, class S>
    void connect(T* obj, S&& f, bool active = true, bool remove_too = false) {
        info() << (active ? "Connecting " : "Disconnecting ") << (remove_too ? "and removing " : "") << signal_name  << " living at " << this << " from object " << obj << " to " << &f ;
        internal::connect_i<S, typename slot_holder<S>::FT,
                slot_holder<S>> (this, obj, std::forward<S>(f), slot_holders, active, remove_too);
    }

    template<class T, class S>
    void disconnect(T*obj, S&& f, bool remove_too = false) {
        connect<T, S>(obj, std::forward<S>(f), false, remove_too);
    }

    signal<Args...>& operator()(Args... args) {
        call_args = std::tuple<Args...>(args...);
        return *this;
    }

    std::string name() const {return signal_name;}
};

template<class T, class Si, class So>
void connect(T* obj, Si &&sig, So &&slo) {
    static_assert(!std::is_same<So, std::nullptr_t>::value, "cannot use nullptr as slot");

    debug() << "Connecting " << &sig << " ("<< sig.name()  << ")"<< " to " << &slo << " living in obj:" << obj ;

    std::forward<Si>(sig).connect(obj, std::forward<So>(slo));
}

template<class T>
T *sender() {
    if(internal::emitter<T>::instance()) {
        return internal::emitter<T>::instance()->sender();
    }
    throw std::runtime_error("not in an emit call");
}

#define emit miso::internal::emitter<std::remove_pointer<decltype(this)>::type>(*this) <<

}

#endif
