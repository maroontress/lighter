#ifndef com_maroontress_lighter_toString_fallback_HXX
#define com_maroontress_lighter_toString_fallback_HXX

#include <sstream>
#include <string>

namespace maroontress::lighter {
    template <typename U>
    std::string toString(U b) {
        if constexpr (std::is_null_pointer<U>::value) {
            return "nullptr";
        } else if constexpr (std::is_same<U, bool>::value) {
            return b ? "true" : "false";
        } else if constexpr (std::is_pointer<U>::value) {
            if (b == nullptr) {
                return "nullptr";
            }
            std::stringstream s;
            s << std::hex << (const void *)b;
            return s.str();
        } else if constexpr (std::is_same<U, std::string>::value) {
            std::stringstream s;
            s << '"' << b << '"';
            return s.str();
        } else if constexpr (std::is_same<U, int>::value
                || std::is_same<U, std::size_t>::value) {
            return std::to_string(b);
        } else if constexpr (std::is_same<U, char>::value) {
            std::stringstream s;
            s << "'" << b << "'";
            return s.str();
        } else {
            return "(unknown)";
        }
    }
}

#endif
