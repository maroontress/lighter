#ifndef com_maroontress_lighter_Report_HXX
#define com_maroontress_lighter_Report_HXX

#include <string>

#include "Reason.hxx"
#include "ReasonConsumer.hxx"

namespace maroontress::lighter {
    class Report final {
    private:
        ReasonConsumer consumer;
        Reason reason;

    public:
        Report(ReasonConsumer consumer, Reason reason)
            : consumer(consumer), reason(reason) {
        }

        std::string getActual() const {
            return reason.getActual();
        }

        Report withActual(std::string newActual) const {
            auto newReason = Reason {reason.getExpected(), newActual};
            return Report {consumer, newReason};
        }

        void print() {
            consumer(reason);
        }
    };
}

#endif
