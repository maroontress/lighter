#ifndef com_maroontress_lighter_StringDecorator_HXX
#define com_maroontress_lighter_StringDecorator_HXX

#include <functional>
#include <string>

namespace maroontress::lighter {
    using StringDecorator = std::function<std::string(const std::string&)>;
}

#endif
