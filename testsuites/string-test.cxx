#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f) == "hello";
        });
    t.toFail([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f) != "hello";
        }, [](Reason r) {
            return match(r,
                "x != \"hello\"",
                "x was \"hello\"");
        });
    return 0;
}
