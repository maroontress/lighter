#ifndef com_maroontress_lighter_LastStage_HXX
#define com_maroontress_lighter_LastStage_HXX

#include <stdexcept>
#include <string>
#include <optional>

#include "ChildStage.hxx"
#include "Messages.hxx"
#include "Report.hxx"

namespace maroontress::lighter {
    template <typename T, typename U>
    class LastStage : public ChildStage<T, U> {
    protected:
        LastStage(std::shared_ptr<Stage<T>> parent)
                : ChildStage<T, U>(parent) {
        }

    public:
        virtual std::optional<U> supply() override final {
            throw std::runtime_error(Messages::ILLEGAL_STATE);
        }

        virtual bool apply(const std::optional<Report>&) override final {
            throw std::runtime_error(Messages::ILLEGAL_STATE);
        }

        virtual std::string description() const override final {
            throw std::runtime_error(Messages::ILLEGAL_STATE);
        }

        virtual std::string status() const override final {
            throw std::runtime_error(Messages::ILLEGAL_STATE);
        }
    };
}

#endif
