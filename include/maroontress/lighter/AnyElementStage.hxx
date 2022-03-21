#ifndef com_maroontress_lighter_AnyElementStage_HXX
#define com_maroontress_lighter_AnyElementStage_HXX

#include <functional>

#include "Actualizer.hxx"
#include "ElementStage.hxx"
#include "Predicate.hxx"
#include "Reason.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"

namespace maroontress::lighter {
    template <typename T, typename U = typename T::value_type>
    class AnyElementStage final : public ElementStage<T, U> {
    private:
        inline static const std::string NOT_FOUND
                {"none of the elements met that requirement"};
        inline static const std::string NO_ELEMENT
                {"there is no element"};

    public:
        AnyElementStage(std::shared_ptr<Stage<T>> parent)
                : ElementStage<T, U>(parent) {
        }

        virtual void eval(Predicate<U> predicate, StringDecorator decorate,
                [[maybe_unused]] StringDecorator toSubject,
                [[maybe_unused]] Actualizer<U> toActual,
                ReasonConsumer consumer) override {
            auto parent = this->getParent();
            auto any = [&]() -> std::optional<std::size_t> {
                for (std::size_t count = 0;; ++count) {
                    auto maybe = this->supply();
                    if (!maybe.has_value()) {
                        return std::make_optional(count);
                    }
                    if (predicate(maybe.value())) {
                        return std::nullopt;
                    }
                }
            };
            auto e = decorate(description());
            auto notFound = Reason {e, NOT_FOUND};
            auto noElement = Reason {e, NO_ELEMENT};
            auto report = [&](std::size_t count) {
                auto& reason = (count == 0) ? noElement : notFound;
                return Report {consumer, reason};
            };
            for (;;) {
                auto maybeError = any();
                auto maybeReport = (!maybeError.has_value())
                    ? std::nullopt
                    : std::make_optional(report(maybeError.value()));
                if (parent->apply(maybeReport)) {
                    return;
                }
                this->next();
            }
        }

        virtual bool apply(const std::optional<Report>& maybeReport) override {
            if (!maybeReport.has_value()) {
                return true;
            }
            if (!this->hasNext()) {
                auto parent = this->getParent();
                auto i = this->getIndex();
                auto& m = (i != -1) ? NOT_FOUND : NO_ELEMENT;
                auto newActual = "as for " + parent->status() + ", " + m;
                maybeReport.value().withActual(newActual).print();
                return true;
            }
            return false;
        }

        virtual std::string description() const override {
            auto parent = this->getParent();
            return "any element of ("
                + parent->description()
                + ")";
        }
    };
}
#endif
