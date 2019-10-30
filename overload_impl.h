#ifndef OVERLOAD_IMPL_H
#define OVERLOAD_IMPL_H

#include <tuple>

template <class ... Fs>
struct overload : Fs... {
    overload(Fs&&... fs) : Fs{fs}... {}
    using Fs::operator()...;
};

template <class ... Fs>
struct overload_unref : overload<Fs...> {
    overload_unref(Fs&&... fs)
	: overload<Fs...>{std::forward<Fs>(fs)...}
    {}

    using overload<Fs...>::operator();

    template <class T>
    auto operator()(std::reference_wrapper<T> rw){
	return (*this)(rw.get());
    }
};

#endif // OVERLOAD_IMPL_H
