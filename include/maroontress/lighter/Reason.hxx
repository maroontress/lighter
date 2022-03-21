#ifndef com_maroontress_lighter_Reason_HXX
#define com_maroontress_lighter_Reason_HXX

#include <string>

namespace maroontress::lighter {
    class Reason final {
    private:
        std::string expected;
        std::string actual;

    public:
        Reason(const std::string& expected, const std::string& actual)
                : expected(expected), actual(actual) {
        }

        const std::string& getExpected() const {
            return expected;
        }

        const std::string& getActual() const {
            return actual;
        }
    };
}

#endif
