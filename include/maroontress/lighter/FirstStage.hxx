#ifndef com_maroontress_lighter_FirstStage_HXX
#define com_maroontress_lighter_FirstStage_HXX

#include <stdexcept>
#include <functional>
#include <string>
#include <optional>

#include "Actualizer.hxx"
#include "Messages.hxx"
#include "Predicate.hxx"
#include "Reason.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"
#include "Stage.hxx"
#include "StringDecorator.hxx"

namespace maroontress::lighter {
    template <typename T>
    class FirstStage final : public Stage<T> {
    private:
        std::optional<T> maybeValue;
        std::string text;

    public:
        FirstStage(T value, std::string description)
                : maybeValue(std::make_optional(value)), text(description) {
        }

        virtual std::optional<T> supply() override {
            auto o = maybeValue;
            maybeValue.reset();
            return o;
        }

        virtual void eval(Predicate<T> predicate, StringDecorator decorate,
                StringDecorator toSubject, Actualizer<T> toActual,
                ReasonConsumer consumer) override {
            if (!maybeValue.has_value()) {
                throw std::runtime_error(Messages::ILLEGAL_STATE);
            }
            auto v = maybeValue.value();
            if (predicate(v)) {
                return;
            }
            auto e = decorate(text);
            auto a = toSubject(text) + " was " + toActual(v);
            auto reason = Reason {e, a};
            auto report = Report {consumer, reason};
            report.print();
        }

        virtual bool apply(const std::optional<Report>& maybeReport) override {
            if (maybeReport.has_value()) {
                auto report = maybeReport.value();
                report.print();
            }
            return true;
        }

        virtual std::string description() const override {
            return text;
        }

        virtual std::string status() const override {
            return text;
        }
    };
}

#endif
