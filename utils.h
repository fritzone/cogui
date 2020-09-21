#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace cogui {

namespace utils {

template <class T>
T repeat(T str, const std::size_t n)
{
    if (n == 0) {
    str.clear();
    str.shrink_to_fit();
    return str;
    }

    if (n == 1 || str.empty()) return str;

    const auto period = str.size();

    if (period == 1) {
    str.append(n - 1, str.front());
    return str;
    }

    str.reserve(period * n);

    std::size_t m {2};

    for (; m < n; m *= 2) str += str;

    str.append(str.c_str(), (n - (m / 2)) * period);

    return str;
}

template <typename S, typename T, typename = std::enable_if<std::is_integral<T>::value> >
S operator*(S str, const T n)
{
    return repeat(std::move(str), static_cast<std::size_t>(n));
}

static std::wstring repeated(int l, std::wstring chr)
{
    return chr * l;
}



}

}

#endif // UTILS_H
