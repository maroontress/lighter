#ifndef com_maroontress_lighter_EveryElementStage_HXX
#define com_maroontress_lighter_EveryElementStage_HXX

#include <functional>

#include "Actualizer.hxx"
#include "ElementStage.hxx"
#include "Predicate.hxx"
#include "Reason.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"
#include "StringDecorator.hxx"

namespace maroontress::lighter {
    template <typename T, typename U = typename T::value_type>
    class EveryElementStage final : public ElementStage<T, U> {
    public:
        EveryElementStage(std::shared_ptr<Stage<T>> parent)
                : ElementStage<T, U>(parent) {
        }

        virtual void eval(Predicate<U> predicate, StringDecorator decorate,
                StringDecorator toSubject, Actualizer<U> toActual,
                ReasonConsumer consumer) override {
            auto parent = this->getParent();
            auto every = [&]() -> std::optional<std::string> {
                for (;;) {
                    auto maybe = this->supply();
                    if (!maybe.has_value()) {
                        return std::nullopt;
                    }
                    auto&& v = *maybe;
                    if (!predicate(v)) {
                        return std::make_optional(toActual(v));
                    }
                }
            };
            auto e = decorate(description());
            auto report = [&](std::string v) {
                auto a = toSubject(this->status()) + " was " + v;
                auto reason = Reason {e, a};
                return Report {consumer, reason};
            };
            for (;;) {
                auto maybeError = every();
                auto maybeReport = !maybeError.has_value()
                    ? std::nullopt
                    : std::make_optional(report(maybeError.value()));
                if (parent->apply(maybeReport)) {
                    return;
                }
                this->next();
            }
        }

        virtual bool apply(const std::optional<Report>& maybeReport) override {
            if (maybeReport.has_value()) {
                auto report = maybeReport.value();
                auto newActual = "as for " + this->status() + ", "
                    + report.getActual();
                report.withActual(newActual).print();
                return true;
            }
            if (!this->hasNext()) {
                return true;
            }
            return false;
        }

        virtual std::string description() const override {
            auto parent = this->getParent();
            return "every element of ("
                + parent->description()
                + ")";
        }
    };
}

#endif
