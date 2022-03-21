#ifndef com_maroontress_lighter_Actualizer_HXX
#define com_maroontress_lighter_Actualizer_HXX

#include <functional>
#include <string>

namespace maroontress::lighter {
    template <typename T>
    using Actualizer = std::function<std::string(const T&)>;
}

#endif
