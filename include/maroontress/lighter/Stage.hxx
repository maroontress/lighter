#ifndef com_maroontress_lighter_Stage_HXX
#define com_maroontress_lighter_Stage_HXX

#include <functional>
#include <optional>
#include <string>

#include "Actualizer.hxx"
#include "Predicate.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"
#include "StringDecorator.hxx"
#include "toString.hxx"

namespace maroontress::lighter {
    template <typename T>
    class Stage {
    public:
        virtual ~Stage() {
        }

        void eval(Predicate<T> predicate, StringDecorator decorate,
                ReasonConsumer consumer) {
            auto toSubject = [](const std::string& v) {
                return v;
            };
            auto toActual = [](const T& v) {
                return toString(v);
            };
            eval(predicate, decorate, toSubject, toActual, consumer);
        }

        virtual void eval(Predicate<T> predicate, StringDecorator decorate,
                StringDecorator toSubject, Actualizer<T> toActual,
                ReasonConsumer consumer) = 0;

        virtual std::optional<T> supply() = 0;

        virtual bool apply(const std::optional<Report>& maybeReport) = 0;

        virtual std::string description() const = 0;

        virtual std::string status() const = 0;
    };
}

#endif
