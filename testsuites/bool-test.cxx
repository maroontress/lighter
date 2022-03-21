#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            bool x {true};
            expect(x, f).isTrue();
        });
    t.toFail([](ReasonConsumer f) {
            bool x {true};
            expect(x, f).isFalse();
        }, [](Reason r) {
            return match(r,
                "x is false",
                "x was true");
        });

    t.toPass([](ReasonConsumer f) {
            bool y {false};
            expect(y, f).isFalse();
        });
    t.toFail([](ReasonConsumer f) {
            bool y {false};
            expect(y, f).isTrue();
        }, [](Reason r) {
            return match(r,
                "y is true",
                "y was false");
        });
    return 0;
}
