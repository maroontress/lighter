#include <vector>

#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).size() == x.size();
        });
    t.toFail([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).size() != x.size();
        }, [](Reason r) {
            return match(r,
                "the size of (x) != 5",
                "the size of (x) was 5");
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aaa"};
            expect(y, f).anyItem().size() == 2;
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aaa"};
            expect(y, f).anyItem().size() == 4;
        }, [](Reason r) {
            return match(r,
                "the size of (any element of (y)) == 4",
                NOT_FOUND);
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"aa", "bb", "cc"};
            expect(y, f).everyItem().size() == 2;
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aaa"};
            expect(y, f).everyItem().size() <= 2;
        }, [](Reason r) {
            return match(r,
                "the size of (every element of (y)) <= 2",
                "the size of ((y)[2]) was 3");
        });
    return 0;
}
