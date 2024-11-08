#ifndef STRING_TYPE_H
#define STRING_TYPE_H

namespace cogui {


/**
     * @concept StringType
     * @brief Concept to constrain types to various string and character array types.
     *
     * The sole existence of it is to allow the user to have a so easy to use title definitiaon as possible.
     *
     * This concept is used to ensure that the types passed to template parameters
     * are one of the following:
     * - std::string
     * - std::wstring
     * - const char*
     * - const wchar_t*
     * - char*
     * - wchar_t*
     * - Array types (including C-style strings and wide strings)
     */
template<typename S> concept StringType = std::same_as<S, std::string> ||
                     std::same_as<S, std::wstring> ||
                     std::same_as<S, const char*> ||
                     std::same_as<S, const wchar_t*> ||
                     std::same_as<S, char*> ||
                     std::same_as<S, wchar_t*> ||
                     std::is_array_v<S>;
}

#endif // STRING_TYPE_H
