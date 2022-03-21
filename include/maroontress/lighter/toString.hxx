#ifndef com_maroontress_lighter_toString_HXX
#define com_maroontress_lighter_toString_HXX

#if __has_include(<format>)
#include <format>

namespace maroontress::lighter {
    template <typename U>
    std::string toString(U b) {
        if constexpr (std::is_null_pointer<U>::value) {
            return "nullptr";
        } else if constexpr (std::is_same<U, bool>::value) {
            return b ? "true" : "false";
        } else if constexpr (std::is_pointer<U>::value) {
            return b == nullptr
                ? "nullptr"
                : std::format("{}", (const void *)b);
        } else if constexpr (std::is_same<U, std::string>::value) {
            return std::format("\"{}\"", b);
        } else if constexpr (std::is_same<U, int>::value
                || std::is_same<U, std::size_t>::value) {
            return std::to_string(b);
        } else if constexpr (std::is_same<U, char>::value) {
            return std::format("'{}'", b);
        } else {
            return "(unknown)";
        }
    }
}
#else
#include "toString_fallback.hxx"
#endif

#endif
