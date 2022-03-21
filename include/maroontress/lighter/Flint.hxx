#ifndef com_maroontress_lighter_Flint_HXX
#define com_maroontress_lighter_Flint_HXX

#include <memory>
#include <functional>
#include <optional>
#include <type_traits>

#include "toString.hxx"
#include "Reason.hxx"
#include "ReasonConsumer.hxx"
#include "Report.hxx"
#include "Stage.hxx"
#include "FirstStage.hxx"
#include "SizeStage.hxx"
#include "AnyElementStage.hxx"
#include "EveryElementStage.hxx"
#include "Container.hxx"

namespace maroontress::lighter {
    template <typename T>
    class Flint {
    private:
        std::shared_ptr<Stage<T>> stage;
        ReasonConsumer consumer;

    public:
        Flint(std::shared_ptr<Stage<T>> stage, ReasonConsumer consumer)
                : stage(stage), consumer(consumer) {
        }

        Flint(T v, std::string d, ReasonConsumer consumer)
                : stage(std::make_shared<FirstStage<T>>(v, d)),
                consumer(consumer) {
        }

        auto size() const requires Container<T> {
            using U = std::size_t;
            return Flint<U>(std::make_shared<SizeStage<T>>(stage), consumer);
        }

        auto anyItem() const requires Container<T> {
            using U = typename T::value_type;
            return Flint<U>(std::make_shared<AnyElementStage<T, U>>(stage),
                consumer);
        }

        auto everyItem() const requires Container<T> {
            using U = typename T::value_type;
            return Flint<U>(std::make_shared<EveryElementStage<T, U>>(stage),
                consumer);
        }

        auto isFalse() const requires std::is_convertible_v<T, bool> {
            auto p = [](const T& a) {
                return !a;
            };
            auto d = [](const std::string m) {
                return m + " is false";
            };
            stage->eval(p, d, consumer);
        }

        auto isTrue() const requires std::is_convertible_v<T, bool> {
            auto p = [](const T& a) {
                return a;
            };
            auto d = [](const std::string m) {
                return m + " is true";
            };
            stage->eval(p, d, consumer);
        }

        auto isNull() const requires std::is_pointer_v<T> {
            auto p = [](const T& a) {
                return a == nullptr;
            };
            auto d = [](const std::string m) {
                return m + " is null";
            };
            stage->eval(p, d, consumer);
        }

        auto isNotNull() const requires std::is_pointer_v<T> {
            auto p = [](const T& a) {
                return a != nullptr;
            };
            auto d = [](const std::string m) {
                return m + " is not null";
            };
            stage->eval(p, d, consumer);
        }

#define com_maroontress_lighter_OO(X) \
        void operator X(const T& expected) const { \
            auto p = [&](const T& a) { \
                return a X expected; \
            }; \
            auto d = [&](const std::string m) { \
                return m + " " #X " " + toString(expected); \
            }; \
            stage->eval(p, d, consumer); \
        }

        com_maroontress_lighter_OO(==)
        com_maroontress_lighter_OO(!=)
        com_maroontress_lighter_OO(<=)
        com_maroontress_lighter_OO(>=)
        com_maroontress_lighter_OO(<)
        com_maroontress_lighter_OO(>)
    };
}

#endif
