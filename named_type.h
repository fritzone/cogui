#ifndef named_type_impl_h
#define named_type_impl_h

#include <type_traits>
#include <utility>
#include <variant>

#include "key.h"

// Enable empty base class optimization with multiple inheritance on Visual Studio.
#if defined(_MSC_VER) && _MSC_VER >= 1910
#  define FLUENT_EBCO __declspec(empty_bases)
#else
#  define FLUENT_EBCO
#endif

namespace fluent
{

template<typename T>
using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

template <typename T, typename Parameter>
class FLUENT_EBCO NamedType
{
public:
    using UnderlyingType = T;

    // constructor
    NamedType() = default;
    explicit constexpr NamedType(T const& value) : value_(value) {}
    template<typename T_ = T, typename = IsNotReference<T_>>
    explicit constexpr NamedType(T&& value) : value_(std::move(value)) {}

    // get
    constexpr T& get() { return value_; }
    constexpr std::remove_reference_t<T> const& get() const {return value_; }

    struct argument
    {
        template<typename U>
        NamedType operator=(U&& value) const
        {
            return NamedType(std::forward<U>(value));
        }
        argument() = default;
        argument(argument const&) = delete;
        argument(argument &&) = delete;
        argument& operator=(argument const&) = delete;
        argument& operator=(argument &&) = delete;

        argument& operator()(const cogui::key&)
        {
            return *this;
        }
    };

private:
    T value_;
};

template<template<typename T> class StrongType, typename T>
constexpr StrongType<T> make_named(T const& value)
{
    return StrongType<T>(value);
}

} // namespace fluent

#endif /* named_type_impl_h */
