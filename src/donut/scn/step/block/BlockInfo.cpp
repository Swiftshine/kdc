#include "scn/step/block/BlockInfo.hpp"

using scn::step::block::BlockInfo;

BlockInfo::BlockInfo()
    : mKind(static_cast<map::BinGmkBlockKind>(60))
    , mGridPos()
{ }

#pragma push
#pragma global_optimizer off // i shouldn't need this
bool BlockInfo::isValid() const {
    bool ret = false;
    s32 kind = static_cast<s32>(mKind);

    if (kind >= 0 && kind <= 59) {
        ret = true;
    }

    return ret;
}
#pragma pop
