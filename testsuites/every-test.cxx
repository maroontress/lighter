#include <vector>

#include "test.hxx"

int main()
{
    using maroontress::lighter::Reason;
    using ReasonConsumer = std::function<void(Reason)>;
    Test t {};

    t.toPass([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).everyItem() >= 'e';
        });
    t.toFail([](ReasonConsumer f) {
            std::string x {"hello"};
            expect(x, f).everyItem() < 'i';
        }, [](Reason r) {
            return match(r,
                "every element of (x) < 'i'",
                "(x)[2] was 'l'");
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aaa"};
            expect(y, f).everyItem().everyItem() == 'a';
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aaa"};
            expect(y, f).everyItem().everyItem() == 'b';
        }, [](Reason r) {
            return match(r,
                "every element of (every element of (y)) == 'b'",
                "as for (y)[0], ((y)[0])[0] was 'a'");
        });
    t.toFail([](ReasonConsumer f) {
            std::vector<std::string> y {"a", "aa", "aba"};
            expect(y, f).everyItem().everyItem() == 'a';
        }, [](Reason r) {
            return match(r,
                "every element of (every element of (y)) == 'a'",
                "as for (y)[2], ((y)[2])[1] was 'b'");
        });

    t.toPass([](ReasonConsumer f) {
            std::vector<std::string> z {};
            expect(z, f).everyItem() == "a";
        });
    return 0;
}
