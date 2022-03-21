#ifndef expect_HXX
#define expect_HXX

#if __has_include(<source_location>)
#include <source_location>

#include "maroontress/lighter/Flint.hxx"

#define expect(x) maroontress::lighter::Flint {(x), #x, [](auto r) { \
        const auto& w = std::source_location::current(); \
        std::cout \
            << w.file_name() << ":" << w.line() << ": error:" << std::endl \
            << "  Expected: " << r.getExpected() << std::endl \
            << "  Actual:   " << r.getActual() << std::endl; \
    }}
#else
#include "expect_fallback.hxx"
#endif

#endif
