#pragma peephole off
#include <donut/hid/Button.hpp>

using hid::Button;

void Button::update(u32 buttonFlags) {
    u32 oldHold = mHold;
    mHold = buttonFlags;
    mTrigger = mHold & ~oldHold;
    mRelease = oldHold & ~mHold;
}

bool Button::isHold(u32 buttonFlags) const {
    return mHold & buttonFlags;
}

bool Button::isTrigger(u32 buttonFlags) const {
    return mTrigger & buttonFlags;
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

Button::Button()
    : mHold(0)
    , mTrigger(0)
    , mRelease(0)
{}

u32 Button::hold() const {
    return mHold;
}

u32 Button::trigger() const {
    return mTrigger;
}

u32 Button::release() const {
    return mRelease;
}
