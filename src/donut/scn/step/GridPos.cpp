#include <hel/math/Math.hpp>
#include "scn/step/GridPos.hpp"

using namespace scn::step;
using hel::math::Vector2;

GridPos::GridPos()
    : x(0)
    , y(0)
{ }

GridPos::GridPos(s32 _x, s32 _y)
    : x(_x)
    , y(_y)
{ }

GridPos::GridPos(const hel::math::Vector2& rPos)
    : x(static_cast<s32>(hel::math::Math::FloorF(rPos.x)))
    , y(static_cast<s32>(hel::math::Math::FloorF(rPos.y)))
{ }

Vector2 GridPos::toWorldPos() const {
    return Vector2(static_cast<float>(x), static_cast<float>(y));
}

// https://decomp.me/scratch/741Wn
Vector2 GridPos::toWorldPosAtCenter() const {
    GridPos gp1(x + 1, y + 1);
    Vector2 pos1 = gp1.toWorldPos();
    Vector2 temp = toWorldPos();
    Vector2 temp1;
    Vector2 temp2;
    temp1 = temp + pos1;
    temp2 = temp1 * 0.5f;
    return temp2;
}

bool GridPos::isPositivePos() const {
    return x >= 0 && y >= 0;
}
