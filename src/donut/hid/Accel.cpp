#pragma peephole off
#include <donut/hid/Accel.hpp>

using hid::Accel;

Accel::Accel()
    : mRaw(Vec())
{ }

//NOTE: All functions below are code merged into others. Refer to the header for more details

void Accel::update(const Vec& rAccel) {
    mRaw.x = rAccel.x;
    mRaw.y = rAccel.y;
    mRaw.z = rAccel.z;
}

Vec Accel::raw() const {
    return mRaw;
}
