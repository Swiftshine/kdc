#pragma peephole off
#include <donut/hid/DPD.hpp>

using hid::DPD;

DPD::DPD()
    : mDist(0.0f)
    , mPos(Vec2())
    , mHori(Vec2())
{ }

void DPD::update(f32 dist, const Vec2& rPos, const Vec2& rHori) {
    mDist = dist;
    mPos = rPos;
    mHori = rHori;
}
