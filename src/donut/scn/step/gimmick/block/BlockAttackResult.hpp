#ifndef DONUT_SCN_STEP_GIMMICK_BLOCK_BLOCKATTACKRESULT_HPP
#define DONUT_SCN_STEP_GIMMICK_BLOCK_BLOCKATTACKRESULT_HPP

#include <types.h>
#include <hel/common/MutableArray.hpp>

#include "scn/step/block/BlockInfo.hpp"

namespace scn { namespace step { namespace gimmick { namespace block {

class BlockAttackResult {
public:
    BlockAttackResult() { }
    ~BlockAttackResult();
private:
    /* 0x000 */ hel::common::MutableArray<step::block::BlockInfo, 64> mBlockInfos;
    /* 0x300 */ int m_300;
    /* 0x304 */ hel::common::MutableArray<bool, 64> mEnabled; // probably
};

}}}}

#endif
