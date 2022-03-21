#ifndef com_maroontress_lighter_ChildStage_HXX
#define com_maroontress_lighter_ChildStage_HXX

#include <memory>

#include "Stage.hxx"

namespace maroontress::lighter {
    template <typename T, typename U>
    class ChildStage : public Stage<U> {
    private:
        std::shared_ptr<Stage<T>> parent;

    public:
        std::shared_ptr<Stage<T>> getParent() const {
            return parent;
        }

        virtual ~ChildStage() {
        }

    protected:
        ChildStage(std::shared_ptr<Stage<T>> parent) : parent(parent) {
        }
    };
}

#endif
