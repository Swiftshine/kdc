#ifndef DONUT_SCN_STEP_BLOCK_BLOCKINFO_HPP
#define DONUT_SCN_STEP_BLOCK_BLOCKINFO_HPP

#include "scn/step/GridPos.hpp"
#include "scn/step/map/BinGmkBlockKind.hpp"

namespace scn { namespace step { namespace block {

class BlockInfo {
public:
    BlockInfo();
    BlockInfo(map::BinGmkBlockKind kind, const GridPos& rPos);
    map::BinGmkBlockKind kind() const;
    const GridPos& gridPos() const;
    bool isValid() const;
private:
    /* 0x0 */ map::BinGmkBlockKind mKind;
    /* 0x4 */ GridPos mGridPos;
};


}}}

#endif
