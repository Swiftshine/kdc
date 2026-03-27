#pragma peephole off
#include <hel/math/Direction3.hpp>
#include <hel/math/Matrix34.hpp>

using hel::math::Direction3;
using hel::math::Vector3;
using hel::math::Matrix34;

Direction3 Direction3::BASIS = Direction3(Vector3(0.0f, 0.0f, 1.0f),
    Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
Direction3 Direction3::FRONT_TO_RIGHT = Direction3(Vector3(1.0f, 0.0f, 0.0f),
    Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
Direction3 Direction3::FRONT_TO_LEFT = Direction3(Vector3(-1.0f, 0.0f, 0.0f),
    Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

void Direction3::normalize() {
    mFront.normalize();
    mUp.normalize();
    mLeft.normalize();
}

//https://decomp.me/scratch/avNdn
//I highly doubt this a weak symbol since A. nothing in this tu uses it and B. it has a direction which means theres a possibility they put this here
Matrix34::Matrix34(const Direction3& rDirection, const Vector3& rVector) {
    mBaseMtx[0][0] = rDirection.mLeft.x;
    mBaseMtx[1][0] = rDirection.mLeft.y;
    mBaseMtx[2][0] = rDirection.mLeft.z;
    mBaseMtx[0][1] = rDirection.mUp.x;
    mBaseMtx[1][1] = rDirection.mUp.y;
    mBaseMtx[2][1] = rDirection.mUp.z;
    mBaseMtx[0][2] = rDirection.mFront.x;
    mBaseMtx[1][2] = rDirection.mFront.y;
    mBaseMtx[2][2] = rDirection.mFront.z;
    mBaseMtx[0][3] = rVector.x;
    mBaseMtx[1][3] = rVector.y;
    mBaseMtx[2][3] = rVector.z;
}

Direction3::Direction3() {
    *this = BASIS;
}

//https://decomp.me/scratch/YYmWC
Direction3::Direction3(const Direction3& rDirection)
    : mFront(rDirection.mFront)
    , mUp(rDirection.mUp)
    , mLeft(rDirection.mLeft)
{ }

//https://decomp.me/scratch/gGg3d
Direction3::Direction3(const Vector3& rFront, const Vector3& rUp, const Vector3& rLeft)
    : mFront(rFront)
    , mUp(rUp)
    , mLeft(rLeft)
{ }

bool Direction3::Left::permittedRestruct() {
    Vector3 second = mDirection->mUp.permittedNormalizedCross(mDirection->mFront);
    if (second.isZero()) {
        return false;
    }
    mDirection->mLeft = second;
    return true;
}

//https://decomp.me/scratch/iTUP7
void Direction3::Up::restruct() {
    mDirection->mUp = mDirection->mFront.normalizedCross(mDirection->mLeft);
}

void Direction3::Left::restruct() {
    mDirection->mLeft = mDirection->mUp.normalizedCross(mDirection->mFront);
}

//https://decomp.me/scratch/Z5xVo
bool Direction3::Up::permittedRestruct() {
    Vector3 second = mDirection->mFront.permittedNormalizedCross(mDirection->mLeft);
    if (second.isZero()) {
        return false;
    }
    mDirection->mUp = second;
    return true;
}

void Direction3::Front::restruct() {
    mDirection->mFront = mDirection->mLeft.normalizedCross(mDirection->mUp);
}

bool Direction3::Front::permittedRestruct() {
    Vector3 second = mDirection->mLeft.permittedNormalizedCross(mDirection->mUp);
    if (second.isZero()) {
        return false;
    }
    mDirection->mFront = second;
    return true;
}

//TODO: add hel::common::FixedStringIN<char, 384>::FromFormat(const char*, ...),
//which seems to be here due to an unused Direction3::toShortString function
