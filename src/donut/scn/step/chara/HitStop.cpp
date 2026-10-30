#include "scn/step/chara/HitStop.hpp"

using namespace scn::step::chara;

HitStop::HitStop()
    : mFrame(0)
    , mFramePre(0)
    , m_8(false)
    , mIsSoft(false)
    , mIsLocked(false)
    , mCallback(nullptr)
{ }

HitStop::HitStop(IHitStopCallBack& callback)
    : mFrame(0)
    , mFramePre(0)
    , m_8(false)
    , mIsSoft(false)
    , mIsLocked(false)
    , mCallback(&callback)
{ }

void HitStop::update()
{
    if (mFrame != 0)
    {
        mFrame--;
    }

    bool isContinue = mFrame != 0;
    if (isContinue != m_8)
    {
        m_8 = isContinue;
        if (mCallback != nullptr)
        {
            if (isContinue)
            {
                mCallback->UnkC();
            }
            else
            {
                mCallback->Unk10();
            }
        }
    }
    mFramePre = mFrame;
}

void HitStop::set(u32 frame)
{
    if (mIsLocked)
    {
        return;
    }

    if (frame == 0)
    {
        return;
    }

    if (!mIsSoft && frame <= mFrame)
    {
        return;
    }

    mFrame = frame;
    mIsSoft = false;
}

void HitStop::setSoft(u32 frame)
{
    if (mIsLocked)
    {
        return;
    }

    if (frame == 0)
    {
        return;
    }

    if (frame <= mFrame)
    {
        return;
    }

    mFrame = frame;
    mIsSoft = true;
}

void HitStop::clear()
{
    if (mFrame == 0)
    {
        return;
    }

    mFrame = 0;
    mIsSoft = false;
}
