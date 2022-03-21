#ifndef com_maroontress_lighter_ElementStage_HXX
#define com_maroontress_lighter_ElementStage_HXX

#include <optional>

#include "ChildStage.hxx"
#include "Element.hxx"

namespace maroontress::lighter {
    template <typename T, typename U = typename T::value_type>
    class ElementStage : public ChildStage<T, U> {
    private:
        std::optional<T> i;
        std::optional<Element<T>> children = std::nullopt;

    protected:
        ElementStage(std::shared_ptr<Stage<T>> parent)
                : ChildStage<T, U>(parent), i(parent->supply()) {
        }

        bool hasNext() {
            if (!i.has_value()) {
                return false;
            }
            if (!children.has_value()) {
                children = std::make_optional(Element {i.value()});
            }
            return children->hasNext();
        }

        void next() {
            auto parent = this->getParent();
            i = parent->supply();
            children = std::nullopt;
        }

        int getIndex() const {
            return (!children.has_value()) ? -1 : children->getIndex();
        }

    public:
        virtual std::optional<U> supply() override final {
            if (!hasNext()) {
                return std::nullopt;
            }
            return std::make_optional(children->next());
        }

        virtual std::string status() const override final {
            auto parent = this->getParent();
            return "(" + parent->status() + ")["
                + std::to_string(this->getIndex()) + "]";
        }
    };
}

#endif
