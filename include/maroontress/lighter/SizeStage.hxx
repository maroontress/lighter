#ifndef com_maroontress_lighter_SizeStage_HXX
#define com_maroontress_lighter_SizeStage_HXX

#include <stdexcept>
#include <string>
#include <optional>

#include "Actualizer.hxx"
#include "LastStage.hxx"
#include "Predicate.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"
#include "StringDecorator.hxx"

namespace maroontress::lighter {
    template <typename T, typename U = typename std::size_t>
    class SizeStage final : public LastStage<T, U> {
    public:
        SizeStage(std::shared_ptr<Stage<T>> parent)
                : LastStage<T, U>(parent) {
        }

        virtual void eval(Predicate<U> predicate, StringDecorator decorate,
                [[maybe_unused]] StringDecorator toSubject,
                Actualizer<U> toActual, ReasonConsumer consumer) override {
            auto parent = this->getParent();
            auto p = [&](const T& v) {
                return predicate(v.size());
            };
            auto d = [&](const std::string& m) {
                return decorate(subject(m));
            };
            auto t = [&](const T& v) {
                return toActual(v.size());
            };
            parent->eval(p, d, subject, t, consumer);
        }

    private:
        static std::string subject(const std::string& m) {
            return "the size of (" + m + ")";
        }
    };
}

#endif
