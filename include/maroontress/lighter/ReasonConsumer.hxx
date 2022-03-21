#ifndef com_maroontress_lighter_ReasonConsumer_HXX
#define com_maroontress_lighter_ReasonConsumer_HXX

#include <functional>

#include "Reason.hxx"

namespace maroontress::lighter {
    using ReasonConsumer = std::function<void(Reason)>;
}

#endif
