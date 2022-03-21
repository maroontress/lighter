#ifndef com_maroontress_lighter_Container_HXX
#define com_maroontress_lighter_Container_HXX

#include <concepts>

namespace maroontress::lighter {
    template <typename T>
    concept Container = requires (T& c) {
        {c.begin()} -> std::same_as<typename T::iterator>;
        {c.end()} -> std::same_as<typename T::iterator>;
        {c.size()} -> std::same_as<std::size_t>;
    };
}

#endif
