#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RecoverMasterSword : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RecoverMasterSword, ksys::act::ai::Action)
public:
    explicit RecoverMasterSword(const InitArg& arg);
    ~RecoverMasterSword() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
