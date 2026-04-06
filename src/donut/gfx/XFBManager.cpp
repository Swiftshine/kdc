#pragma peephole off
#include <donut/mem/Memory.hpp>
#include <donut/gfx/XFBManager.hpp>
#include <revolution/VI.h>

using gfx::XFBManager;

XFBManager::XFBManager(const gfx::VISetting& rVISetting)
    : mTarget1(rVISetting.fbSize(), 0x20, mem::Memory::Instance->mem2FixHeap())
    , mTarget2(rVISetting.fbSize(), 0x20, mem::Memory::Instance->mem2FixHeap())
    , mIsDrawTarget1(false)
{
    VISetNextFrameBuffer(drawTargetXFB());
    VIWaitForRetrace();
    changeDrawTargetXFB();
}

void* XFBManager::drawTargetXFB() {
    if (mIsDrawTarget1) {
        return mTarget1.block().startAddress();
    }

    return mTarget2.block().startAddress();
}

void XFBManager::changeDrawTargetXFB() {
    mIsDrawTarget1 = mIsDrawTarget1 == false;
}

void* XFBManager::target1() {
    return mTarget1.block().startAddress();
}

void* XFBManager::target2() {
    return mTarget2.block().startAddress();
}
