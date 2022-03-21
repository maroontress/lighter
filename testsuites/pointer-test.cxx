#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            void *x {nullptr};
            expect(x, f).isNull();
        });
    t.toPass([](ReasonConsumer f) {
            void *x {nullptr};
            expect(x, f) == nullptr;
        });
    t.toFail([](ReasonConsumer f) {
            void *x {nullptr};
            expect(x, f).isNotNull();
        }, [](Reason r) {
            return match(r,
                "x is not null",
                "x was nullptr");
        });
    t.toFail([](ReasonConsumer f) {
            void *x {nullptr};
            expect(x, f) != nullptr;
        }, [](Reason r) {
            return match(r,
                "x != nullptr",
                "x was nullptr");
        });

    t.toPass([](ReasonConsumer f) {
            const char *x {"hello"};
            expect(x, f).isNotNull();
        });
    t.toPass([](ReasonConsumer f) {
            const char *x {"hello"};
            expect(x, f) != nullptr;
        });
    t.toFail([](ReasonConsumer f) {
            const char *x {"hello"};
            expect(x, f).isNull();
        }, [](Reason r) {
            return r.getExpected() == "x is null"
                && r.getActual().starts_with("x was 0x");
        });
    t.toFail([](ReasonConsumer f) {
            const char *x {"hello"};
            expect(x, f) == nullptr;
        }, [](Reason r) {
            return r.getExpected() == "x == nullptr"
                && r.getActual().starts_with("x was 0x");
        });
    return 0;
}
