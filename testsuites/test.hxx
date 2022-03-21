#ifndef test_HXX
#define test_HXX

#include <cstdlib>
#include <optional>
#include <iostream>

#include "maroontress/lighter/Flint.hxx"

#define expect(x, f) maroontress::lighter::Flint {(x), #x, (f)}

static bool match(const maroontress::lighter::Reason& r,
    const std::string& expected, const std::string& actual)
{
    return r.getExpected() == expected && r.getActual() == actual;
}

static const char NOT_FOUND[] {"none of the elements met that requirement"};
static const char NO_ELEMENT[] {"there is no element"};

class Test final {
private:
    using Reason = maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;

    std::optional<Reason> maybeReason;

public:
    void toPass(std::function<void(ReasonConsumer)> f) {
        maybeReason.reset();
        auto reason = [&](Reason r) {
            std::cout << r.getExpected() << std::endl
                << r.getActual() << std::endl;
            maybeReason = std::make_optional(r);
        };
        f(reason);
        if (maybeReason.has_value()) {
            std::exit(1);
        }
    }

    void toFail(std::function<void(ReasonConsumer)> f,
            std::function<bool(Reason)> g) {
        maybeReason.reset();
        auto reason = [&](Reason r) {
            std::cout << r.getExpected() << std::endl
                << r.getActual() << std::endl;
            maybeReason = std::make_optional(r);
        };
        f(reason);
        if (!maybeReason.has_value() || !g(*maybeReason)) {
            std::exit(1);
        }
    }
};

#endif
