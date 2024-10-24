#ifndef OVERLOAD_IMPL_H
#define OVERLOAD_IMPL_H

#include <tuple>
#include <variant>

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


template<typename CONN, typename ... Args>
void init(CONN connector, Args... args)
{
	auto tup = std::make_tuple(std::forward<Args>(args)...);
	for (auto const& elem : to_range(tup))
	{
		std::visit(connector, elem);
	}
}
#endif // OVERLOAD_IMPL_H
