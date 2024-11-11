#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include "utils.h"

#include <string>
#include <concepts>
#include <type_traits>

namespace cogui {

/**
 * @concept StringType
 * @brief Concept to constrain types to various string and character array types.
 *
 * This concept is used to ensure that the types passed to template parameters
 * are one of the following:
 * - std::string
 * - std::wstring
 * - std::u8string
 * - std::u16string
 * - std::u32string
 * - const char*
 * - const wchar_t*
 * - const char8_t*
 * - const char16_t*
 * - const char32_t*
 * - char*
 * - wchar_t*
 * - char8_t*
 * - char16_t*
 * - char32_t*
 * - Array types (including C-style strings, wide strings, and UTF strings)
 *
 * Usage:
 * @code
 * template<StringType S, typename ... Args>
 * void log(const S& message);
 * @endcode
 */
template<typename S>
concept StringType = std::same_as<S, std::string> ||
                     std::same_as<S, std::wstring> ||
                     std::same_as<S, std::u8string> ||
                     std::same_as<S, std::u16string> ||
                     std::same_as<S, std::u32string> ||
                     std::same_as<S, const char*> ||
                     std::same_as<S, const wchar_t*> ||
                     std::same_as<S, const char8_t*> ||
                     std::same_as<S, const char16_t*> ||
                     std::same_as<S, const char32_t*> ||
                     std::same_as<S, char*> ||
                     std::same_as<S, wchar_t*> ||
                     std::same_as<S, char8_t*> ||
                     std::same_as<S, char16_t*> ||
                     std::same_as<S, char32_t*> ||
                     std::is_array_v<S> && std::same_as< typename std::remove_all_extents<S>::type , char> ||
                     std::is_array_v<S> && std::same_as< typename std::remove_all_extents<S>::type , wchar_t> ||
                     std::is_array_v<S> && std::same_as< typename std::remove_all_extents<S>::type , char16_t> ||
                     std::is_array_v<S> && std::same_as< typename std::remove_all_extents<S>::type , char32_t>
    ;
}

template<cogui::StringType S>
std::wstring convert_title(const S& title)
{
    if constexpr (std::same_as<S, const char*> || std::same_as<S, std::string> || (std::is_array_v<S> && std::same_as<typename std::remove_extent<S>::type, char>))
    {
        return cogui::utils::std2ws(title);
    }
    else
    {
        return title;
    }
}

#endif // STRING_TYPE_H
