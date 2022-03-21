#include <vector>

#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).anyItem() == 'e';
        });
    t.toFail([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).anyItem() == 'w';
        }, [](Reason r) {
            return match(r,
                "any element of (x) == 'w'",
                NOT_FOUND);
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "ab"};
            expect(y, f).anyItem().anyItem() == 'b';
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "ab"};
            expect(y, f).anyItem().anyItem() == 'c';
        }, [](Reason r) {
            return match(r,
                "any element of (any element of (y)) == 'c'",
                std::string {"as for y, "} + NOT_FOUND);
        });

    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> z {};
            expect(z, f).anyItem() != "a";
        }, [](Reason r) {
            return match(r,
                "any element of (z) != \"a\"",
                NO_ELEMENT);
        });

    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> z {};
            expect(z, f).anyItem().anyItem() == 'a';
        }, [](Reason r) {
            return match(r,
                "any element of (any element of (z)) == 'a'",
                std::string {"as for z, "} + NO_ELEMENT);
        });
    return 0;
}
