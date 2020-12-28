#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetItemGet : public GetItem {
    SEAD_RTTI_OVERRIDE(GetItemGet, GetItem)
public:
    explicit GetItemGet(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
