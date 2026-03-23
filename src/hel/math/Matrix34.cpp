#pragma peephole off
#include <hel/math/Matrix34.hpp>
#include <hel/math/Vector3.hpp>
#include <hel/math/Matrix44.hpp>

using hel::math::Matrix34;
using hel::math::Matrix44;

void Matrix34::CreateTrans(const Vector3& rTrans) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    PSMTXTransApply(mBaseMtx, mBaseMtx, rTrans.x, rTrans.y, rTrans.z);
}

void Matrix34::CreateScale(const Vector3& rScale) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    PSMTXScaleApply(mBaseMtx, mBaseMtx, rScale.x, rScale.y, rScale.z);
}

void Matrix34::CreateRotAxisRad(const Vector3& rAxis, f32 radians) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    nw4r::math::MTX34RotAxisRad(&mBaseMtx, (nw4r::math::VEC3*)&rAxis, radians);
}

void Matrix34::CreateRotAxisDeg(const Vector3& rAxis, f32 degrees) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    nw4r::math::MTX34RotAxisDeg(&mBaseMtx, (nw4r::math::VEC3*)&rAxis, degrees);
}

void Matrix34::CreateRotXYZRad(const Vector3& rRotation) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    nw4r::math::MTX34RotXYZRad(&mBaseMtx, rRotation.x, rRotation.y, rRotation.z);
}

void Matrix34::CreateRotXYZDeg(const Vector3& rRotation) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    nw4r::math::MTX34RotXYZDeg(&mBaseMtx, rRotation.x, rRotation.y, rRotation.z);
}

//https://decomp.me/scratch/haKmQ
void Matrix34::CreateLookAt(const Vector3& rPosition, const Vector3& rUp, const Vector3& rTarget) {
    nw4r::math::MTX34Identity(&mBaseMtx);
    nw4r::math::MTX34LookAt(&mBaseMtx, (nw4r::math::VEC3*)&rPosition,
    (nw4r::math::VEC3*)&rUp, (nw4r::math::VEC3*)&rTarget);
}


inline f32 testInline(f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    return arg1 * arg2 - arg3 * arg4;
}

//https://decomp.me/scratch/6aYu7
void Matrix34::mtxInverse(const Mtx arg1, Mtx arg2) const {
    f32 firstPart = arg1[0][0] * arg1[2][1];
    f32 secondPart = arg1[1][0] * arg1[0][1];
    f32 thirdPart = arg1[2][0] * arg1[1][1];
    f32 fourthPart = arg1[1][0] * arg1[0][2];
    f32 fifthPart = arg1[0][0] * arg1[1][1];
    f32 sixthPart = (arg1[0][1] * arg1[1][2]) * arg1[2][0];

    sixthPart = (arg1[2][2] * fifthPart) + sixthPart;
    sixthPart = (arg1[2][1] * fourthPart) + sixthPart;
    sixthPart =  -((arg1[0][2] *  thirdPart) - sixthPart);
    sixthPart = -((arg1[2][2] * secondPart)  - sixthPart);
    sixthPart = -((arg1[1][2] * firstPart)  - sixthPart);

    if (1e-5f < fabsf(sixthPart)) {
        PSMTXIdentity(arg2);
        return;
    }
    if (arg1 == arg2) {
        Mtx var1;
        PSMTXCopy(arg1, var1);
        arg2 = var1;
    }

    f32 dividedSixthPart = 1.0f / sixthPart;


    arg2[0][0] = dividedSixthPart * (arg1[1][1] * arg1[2][2] - arg1[2][1] * arg1[1][2] );
    arg2[0][1] = dividedSixthPart * -(arg1[0][1] * arg1[2][2] - arg1[2][1] * arg1[0][2] );
    arg2[0][2] = dividedSixthPart * (arg1[0][1] * arg1[1][2] - arg1[1][1] * arg1[0][2] );
    arg2[1][0] = dividedSixthPart * -(arg1[1][0] * arg1[2][2] - arg1[2][0] * arg1[1][2] );
    arg2[1][1] = dividedSixthPart * (arg1[0][0] * arg1[2][2] - arg1[2][0] * arg1[0][2] );
    arg2[1][2] = dividedSixthPart * -(arg1[0][0] * arg1[1][2] - arg1[1][0] * arg1[0][2] );
    arg2[2][0] = dividedSixthPart * (arg1[1][0] * arg1[2][1] - arg1[2][0] * arg1[1][1] );
    arg2[2][1] = dividedSixthPart * -(arg1[0][0] * arg1[2][1] - arg1[2][0] * arg1[0][1] );
    arg2[2][2] = dividedSixthPart * (arg1[0][0] * arg1[1][1] - arg1[1][0] * arg1[0][1] );

    arg2[0][3] = -(arg2[1][0] * arg1[2][3] - (-arg2[0][1] * arg1[0][3] - arg2[0][2] * arg1[1][3] ));
    arg2[1][3] = -(arg2[2][0] * arg1[2][3] - (-arg2[1][1] * arg1[0][3] - arg2[1][2] * arg1[1][3] ));
    arg2[2][3] = -(arg2[2][2] * arg1[2][3] - (-arg2[2][0] * arg1[0][3] - arg2[1][2] * arg1[1][3] ));
}

Matrix44 Matrix34::toMatrix44() const {
    Matrix44 toReturn;

    toReturn.mBaseMtx[0][0] = mBaseMtx[0][0];
    toReturn.mBaseMtx[0][1] = mBaseMtx[0][1];
    toReturn.mBaseMtx[0][2] = mBaseMtx[0][2];
    toReturn.mBaseMtx[0][3] = mBaseMtx[0][3];
    toReturn.mBaseMtx[1][0] = mBaseMtx[1][0];
    toReturn.mBaseMtx[1][1] = mBaseMtx[1][1];
    toReturn.mBaseMtx[1][2] = mBaseMtx[1][2];
    toReturn.mBaseMtx[1][3] = mBaseMtx[1][3];
    toReturn.mBaseMtx[2][0] = mBaseMtx[2][0];
    toReturn.mBaseMtx[2][1] = mBaseMtx[2][1];
    toReturn.mBaseMtx[2][2] = mBaseMtx[2][2];
    toReturn.mBaseMtx[2][3] = mBaseMtx[2][3];
    return toReturn;
}
