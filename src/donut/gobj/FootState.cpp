#pragma peephole off
#include <donut/gobj/FootState.hpp>

using gobj::FootState;

bool FootState::isAir() const {
    return !mOnGround;
}

void FootState::setGround() {
    mOnGround = true;
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

FootState::FootState()
    : mOnGround(false)
{}

bool FootState::isGround() const {
    return mOnGround;
}

void FootState::setAir() {
    mOnGround = false;
}
