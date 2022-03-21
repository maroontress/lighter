#include <vector>

#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "ab", "bbb"};
            expect(y, f).anyItem().everyItem() == 'b';
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "ab", "bbb"};
            expect(y, f).anyItem().everyItem() == 'c';
        }, [](Reason r) {
            return match(r,
                "every element of (any element of (y)) == 'c'",
                std::string("as for y, ") + NOT_FOUND);
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"abc", "ab", "a"};
            expect(y, f).everyItem().anyItem() == 'a';
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"abc", "ab", "a"};
            expect(y, f).everyItem().anyItem() == 'b';
        }, [](Reason r) {
            return match(r,
                "any element of (every element of (y)) == 'b'",
                std::string("as for (y)[2], ") + NOT_FOUND);
        });
    return 0;
}
