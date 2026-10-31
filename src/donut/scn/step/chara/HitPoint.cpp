#include "scn/step/chara/HitPoint.hpp"
#include <algorithm>

using namespace scn::step::chara;

#pragma dont_inline on

HitPoint::HitPoint()
    : mPoints(0)
    , mMax(0)
    , mMin(0)
    , mDeadBent(0)
    , mPrevPoints(0)
    , m_14(0)
{ }

bool HitPoint::isFull() const
{
    return mPoints == mMax;
}

bool HitPoint::isDeadBentZero() const
{
    return mDeadBent == 0;
}

void HitPoint::init(u32 points)
{
    mMax = points;
    mPrevPoints = points;
    mPoints = points;
}

void HitPoint::initDeadBent(u32 deadBent)
{
    mDeadBent = deadBent;
}

// https://decomp.me/scratch/w1Vnj
void HitPoint::dec(u32 amount)
{
    mPrevPoints = mPoints;
    if (mPoints == 0)
    {
        decDeadBent(amount);
        return;
    }

    u32 points = mPoints - amount;
    if (points < mMin)
    {
        mPoints = mMin;
    }
    else
    {
        mPoints = points;
    }

    if (m_14 == 0)
    {
        return;
    }

    if (mPoints != 0)
    {
        return;
    }

    if (mPrevPoints < m_14)
    {
        return;
    }

    mPoints = 1;
}

void HitPoint::inc(u32 amount)
{
    mPrevPoints = mPoints;
    u32 points = mPoints + amount;
    mPoints = std::min<u32>(mMax, points);
}

void HitPoint::set(u32 points)
{
    mPrevPoints = mPoints;
    mPoints = std::max<u32>(mMin, std::min<u32>(mMax, points));
}

void HitPoint::decDeadBent(u32 amount)
{
    if (mDeadBent < amount)
    {
        mDeadBent = 0;
        return;
    }
    mDeadBent -= amount;
}

// https://decomp.me/scratch/QXsxl
void HitPoint::setMin(u32 min)
{
    mMin = min;
    mPoints = std::max<u32>(mMin, mPoints);
}

// https://decomp.me/scratch/v5g99
float HitPoint::rate() const
{
    return mPoints / mMax;
}
