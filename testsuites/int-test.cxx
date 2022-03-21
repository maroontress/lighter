#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {}; 

    t.toPass([](ReasonConsumer f) {
            int x {12};
            expect(x, f) == 12;
        });
    t.toFail([](ReasonConsumer f) {
            int x {12};
            expect(x, f) == 34;
        }, [](Reason r) {
            return match(r,
                "x == 34",
                "x was 12");
        });

    t.toPass([](ReasonConsumer f) {
            int x {12};
            expect(x, f) != 34;
        });
    t.toFail([](ReasonConsumer f) {
            int x {12};
            expect(x, f) != 12 ;
        }, [](Reason r) {
            return match(r,
                "x != 12",
                "x was 12");
        });

    t.toPass([](ReasonConsumer f) {
            int x {12};
            expect(x, f) < 34;
        });
    t.toFail([](ReasonConsumer f) {
            int x {12};
            expect(x, f) > 34;
        }, [](Reason r) {
            return match(r,
                "x > 34",
                "x was 12");
        });

    return 0;
}
