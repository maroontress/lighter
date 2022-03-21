#include <iostream>
#include <vector>

#include "expect.hxx"

static void intExample()
{
    int x {12};

    // PASS
    expect(x) == 12;

    // FAIL
    expect(x) == 13;
}

static void pointerExample()
{
    int x {12};

    // PASS
    expect(&x) != nullptr;
    expect(&x).isNotNull();

    // FAIL
    expect(&x) == nullptr;
    expect(&x).isNull();
}

static void booleanExample()
{
    bool x {false};

    // PASS
    expect(x).isFalse();

    // FAIL
    expect(x).isTrue();
}

static void sizeExample()
{
    std::vector<int> x {12, 23, 34};
    std::initializer_list<std::string> y = {"a", "b"};

    // PASS
    expect(x).size() == 3;
    expect(y).size() == 2;

    // FAIL
    expect(x).size() == 1;
    expect(y).size() == 0;
}

static void anyItemExample()
{
    std::vector<int> x {12, 23, 34};
    std::initializer_list<std::string> y = {"a", "b"};

    // PASS
    expect(x).anyItem() == 23;
    expect(y).anyItem() == "a";

    // FAIL
    expect(x).anyItem() > 45;
    expect(y).anyItem() == "c";
}

static void everyItemExample()
{
    std::vector<int> x {12, 23, 34};
    std::initializer_list<std::string> y = {"a", "b"};

    // PASS
    expect(x).everyItem() < 45;
    expect(y).everyItem() <= "b";

    // FAIL
    expect(x).everyItem() < 20;
    expect(y).everyItem() == "b";
}

static void emptyContainerExample()
{
    std::vector<int> z {};

    // PASS
    expect(z).everyItem() == 10;

    // FAIL
    expect(z).anyItem() == 10;
}

static void anyAndEveryItemExample()
{
    std::vector<std::string> a = {"aaa"}, b = {"bb", "bbb"}, c = {"c", "cc"};
    auto x = {a, b, c};

    // PASS
    expect(x).anyItem().everyItem().size() > 2;

    // FAIL
    expect(x).everyItem().anyItem().size() > 2;
}

int main()
{
    intExample();
    pointerExample();
    booleanExample();
    sizeExample();
    anyItemExample();
    everyItemExample();
    emptyContainerExample();
    anyAndEveryItemExample();
}
