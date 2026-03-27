#include <donut/util/FrameCounter.hpp>

using util::FrameCounter;

void FrameCounter::reset(u32 endFrame) {
    mEndFrame = endFrame;
    reset();
}

bool FrameCounter::isEnd() const {
    return mCurrentFrame == mEndFrame;
}

void FrameCounter::advanceIfNotEnd() {
    if (!isEnd()) {
        advance();
    }
}

void FrameCounter::setEnd() {
    mCurrentFrame = mEndFrame;
}

void FrameCounter::setEndIfNotEnd() {
    if (!isEnd()) {
        setEnd();
    }
}

f32 FrameCounter::normalizedFrame() const {
    if (mEndFrame == 0) {
        return 1.0f;
    }

    return (f32)mCurrentFrame / (f32)mEndFrame;
}

f32 FrameCounter::inversedNormalizedFrame() const {
    return 1.0f - normalizedFrame();
}

void FrameCounter::reset() {
    mCurrentFrame = 0;
}

void FrameCounter::advance() {
    mCurrentFrame++;
}

u32 FrameCounter::frame() const {
    return mCurrentFrame;
}

u32 FrameCounter::maxFrame() const {
    return mEndFrame;
}

FrameCounter::FrameCounter()
    : mEndFrame(0)
    , mCurrentFrame(0)
{ }

FrameCounter::FrameCounter(u32 endFrame)
    : mEndFrame(endFrame)
    , mCurrentFrame(0)
{ }
