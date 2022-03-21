#ifndef com_maroontress_lighter_Predicate_HXX
#define com_maroontress_lighter_Predicate_HXX

#include <functional>

namespace maroontress::lighter {
    template <typename T>
    using Predicate = std::function<bool(const T&)>;
}

#endif
