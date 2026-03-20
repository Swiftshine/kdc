#ifndef DONUT_SCN_STEP_GRIDPOS_HPP
#define DONUT_SCN_STEP_GRIDPOS_HPP

#include <hel/math/Vector2.hpp>

namespace scn { namespace step {

class GridPos {
public:
    GridPos();
    GridPos(s32 _x, s32 _y);
    GridPos(const hel::math::Vector2& rPos);
    hel::math::Vector2 toWorldPos() const;
    hel::math::Vector2 toWorldPosAtCenter() const;
    bool isPositivePos() const;
private:
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
};
}}

#endif
