#ifndef com_maroontress_lighter_Element_HXX
#define com_maroontress_lighter_Element_HXX

#include "Container.hxx"

namespace maroontress::lighter {
    template <typename T>
    class Element {
    private:
        typename T::iterator current;
        typename T::iterator end;
        int i {-1};

    public:
        using E = typename T::value_type;

        Element(T& container) requires Container<T>
            : current(container.begin()), end(container.end()) {
        }

        bool hasNext() const {
            return current != end;
        }

        int getIndex() const {
            return i;
        }

        E next() {
            auto&& v = *current;
            ++current;
            ++i;
            return v;
        }
    };
}

#endif
