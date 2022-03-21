# Lighter

Lighter is a header-only library in C++20 to check assertions.

## Examples

In preparation, define the macro `expect(x)` as follows:

```c++
#define expect(x) maroontress::lighter::Flint {(x), #x, [](auto r) { \
        const auto& w = std::source_location::current(); \
        std::cout \
            << w.file_name() << ":" << w.line() << ": error:" << std::endl \
            << "  Expected: " << r.getExpected() << std::endl \
            << "  Actual:   " << r.getActual() << std::endl; \
    }}
```

The macro `expect(x)` is a trigger to start an assertion, and when the
assertion fails, it calls the lambda expression at the third argument with the
reason for the assertion failure. Note that the macro name `expect` is used
only to illustrate the following examples and can be any name.

### Integers

Here is a simple example of using the macro `expect(x)`:

```c++
int x {12};

// PASS
expect(x) == 12;

// FAIL
expect(x) == 13;
```

The first assertion `expect(x) == 12;` does nothing because the variable `x` is
12. On the other hand, the second `expect(x) != 12;` fails so that it calls
the lambda expression and then prints as follows:

```plaintext
main.cxx:14: error:
  Expected: x == 13
  Actual:   x was 12
```

In addition to `==`, you can also use `!=`, `<`, `>`, `<=`, and `>=` as
operators. Note that the expression `expect(x)` itself does nothing. Comparison
with an operator triggers an evaluation.

### Pointers

For pointers, the member functions `isNull()` and `isNotNull()` are available to
compare the specified value with `nullptr` as follows:

```c++
int x {12};

// PASS
expect(&x) != nullptr;
expect(&x).isNotNull();

// FAIL
expect(&x) == nullptr;
expect(&x).isNull();
```

The last two assertions fail and the console shows:

```plaintext
main.cxx:26: error:
  Expected: &x == nullptr
  Actual:   &x was 0xafc178f4a4
main.cxx:27: error:
  Expected: &x is null
  Actual:   &x was 0xafc178f4a4
```

### Booleans

For booleans, the member functions `isTrue()` and `isFalse()` are available:

```c++
bool x {false};

// PASS
expect(x).isFalse();

// FAIL
expect(x).isTrue();
```

The last assertion fails and the console shows:

```plaintext
main.cxx:38: error:
  Expected: x is true
  Actual:   x was false
```

### Containers

Let's look at more complex use cases. For containers, the following member
functions are available:

- `size()`
- `anyItem()`
- `everyItem()`

The function `size()` transforms the container to its size as follows:

```c++
std::vector<int> x {12, 23, 34};
std::initializer_list<std::string> y = {"a", "b"};

// PASS
expect(x).size() == 3;
expect(y).size() == 2;

// FAIL
expect(x).size() == 1;
expect(y).size() == 0;
```

The last two assertions fail and the console shows:

```plaintext
main.cxx:51: error:
  Expected: the size of (x) == 1
  Actual:   the size of (x) was 3
main.cxx:52: error:
  Expected: the size of (y) == 0
  Actual:   the size of (y) was 2
```

The function `anyItem()` transforms the container to its elements. The
assertion fails only when none of them meets the requirement on the right-hand
side of `anyItem()`.

```c++
std::vector<int> x {12, 23, 34};
std::initializer_list<std::string> y = {"a", "b"};

// PASS
expect(x).anyItem() == 23;
expect(y).anyItem() == "a";

// FAIL
expect(x).anyItem() > 45;
expect(y).anyItem() == "c";
```

The last two assertions fail and the console shows:

```plaintext
main.cxx:65: error:
  Expected: any element of (x) > 45
  Actual:   none of the elements met that requirement
main.cxx:66: error:
  Expected: any element of (y) == "c"
  Actual:   none of the elements met that requirement
```

The function `everyItem()` also transforms the container to its elements.
However, the assertion fails when at least one of them does not meet the
requirement on the right-hand side of `everyItem()`.

```c++
std::vector<int> x {12, 23, 34};
std::initializer_list<std::string> y = {"a", "b"};

// PASS
expect(x).everyItem() < 45;
expect(y).everyItem() <= "b";

// FAIL
expect(x).everyItem() < 20;
expect(y).everyItem() == "b";
```

The last two assertions fail and the console shows:

```plaintext
main.cxx:79: error:
  Expected: every element of (x) < 20
  Actual:   (x)[1] was 23
main.cxx:80: error:
  Expected: every element of (y) == "b"
  Actual:   (y)[0] was "a"
```

If the container is empty, the behavior of `anyItem()` and `everyItem()` is
quite different. For empty containers, the `anyItem()` always fails, while
`everyItem()` always succeeds as follows:

```c++
std::vector<int> z {};

// PASS
expect(z).everyItem() == 10;

// FAIL
expect(z).anyItem() == 10;
```

The last assertion fails and the console shows:

```plaintext
main.cxx:91: error:
  Expected: any element of (z) == 10
  Actual:   there is no element
```

Note that `size()`, `anyItem()`, and `everyItem()` can be combined as follows:

```c++
std::vector<std::string> a = {"aaa"}, b = {"bb", "bbb"}, c = {"c", "cc"};
auto x = {a, b, c};

// PASS
expect(x).anyItem().everyItem().size() > 2;

// FAIL
expect(x).everyItem().anyItem().size() > 2;
```

The last assertion fails and the console shows:

```plaintext
main.cxx:103: error:
  Expected: the size of (any element of (every element of (x))) > 2
  Actual:   as for (x)[2], none of the elements met that requirement
```

> [Run all examples](https://replit.com/@maroontress/cxx20-lighter#main.cxx)
