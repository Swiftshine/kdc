#pragma peephole off
#include <nw4r/math/math_types.h>
#include <cmath>
#include <hel/math/Vector3.hpp>

using hel::math::Vector3;

Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Vector3::ALL_ONE = Vector3(1.0f, 1.0f, 1.0f);
Vector3 Vector3::BASIS_X = Vector3(1.0f, 0.0f, 0.0f);
Vector3 Vector3::BASIS_Y = Vector3(0.0f, 1.0f, 0.0f);
Vector3 Vector3::BASIS_Z = Vector3(0.0f, 0.0f, 1.0f);

Vector3 Vector3::normalizedCross(const Vector3& rOther) const {
    Vector3 crossedValue =  cross(rOther);
    crossedValue.normalize();
    return crossedValue;
}

//https://decomp.me/scratch/QG5VG
Vector3 Vector3::permittedNormalizedCross(const Vector3& rOther) const {
    Vector3 crossVal = cross(rOther);
    f32 normalizedCrossVal = crossVal.permittedNormalize();

    if (normalizedCrossVal == 0.0f) {
        return Vector3();
    }

    return crossVal;

}

f32 Vector3::permittedNormalize() {
    if (length() == 0.0f)  {
        return 0.0f;
    }
    return normalize();
}

f32 Vector3::normalize() {
    f32 lengthVal = length();
    if (lengthVal == 0.0f) {
        return lengthVal;
    }
    *this /= lengthVal;

    if (1.0f <= x) {
        x = 1.0f;
        z = 0.0f;
        y = 0.0f;
    }
    else if (x <= -1.0f) {
        x = -1.0f;
        z = 0.0f;
        y = 0.0f;
    }
    else if (1.0f <= y) {
        y = 1.0f;
        x = 0.0f;
        z = 0.0f;
    }
    else if (y <= -1.0f) {
        y = -1.0f;
        x = 0.0f;
        z= 0.0f;
    }
    else if (1.0f <= z) {
        z = 1.0f;
        y = 0.0f;
        x = 0.0f;
    }
    else if (z <= -1.0f) {
        z = -1.0f;
        y = 0.0f;
        x = 0.0f;
    }
    return lengthVal;
}

void Vector3::operator/=(float scalar) {
    *this *= 1.0f / scalar;
}

void Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

f32 Vector3::setLength(f32 arg1) {
    f32 lengthVar = length();

    if (lengthVar == 0.0f) {
        *this = ZERO;
    } else {
        *this *= (arg1 / lengthVar);
    }
    return lengthVar;
}

f32 Vector3::cos(const Vector3& rOther) const {
    f32 lengthVar = length() *  rOther.length();
    if (lengthVar == 0.0f) {
        return 0.0f;
    }
    f32 cos = dot(rOther) / lengthVar;

    if (1.0f < cos) {
        return 1.0f;
    }
    else if (cos < -1.0f) {
        return -1.0f;
    }
    return cos;
}

bool Vector3::isZeroStrict() const {
    return x == ZERO.x && y == ZERO.y && z == ZERO.z;
}

void Vector3::rotate(const Vector3& rAxis, f32 angle) {
   nw4r::math::MTX34 mtx;
    nw4r::math::MTX34RotAxisFIdx(&mtx, (nw4r::math::VEC3*)&rAxis,  40.743664f * angle);

    *this = Vector3((((mtx._00 * x) + mtx._01 * y) + mtx._02 * z) + mtx._03,
        (((mtx._10 * x) + mtx._11 * y) + mtx._12 * z) + mtx._13,
        (((mtx._20 * x) + mtx._21 * y) + mtx._22 * z) + mtx._23);
}

void Vector3::rotate(Vector3::AxisKind axis, f32 angle) {
    Vector3* axisVec = &ZERO;

    switch (axis) {
        case AXIS_X:
        axisVec = &BASIS_X;
        rotate(*axisVec, angle);
        break;
        case AXIS_Y:
        axisVec = &BASIS_Y;
        rotate(*axisVec, angle);
        break;
        case AXIS_Z:
        axisVec = &BASIS_Z;
        rotate(*axisVec, angle);
        break;
    }
}

//https://decomp.me/scratch/oEsBD
Vector3 Vector3::slerp(const Vector3& rOther, f32 arg1) const {
    f32 dotVal = dot(rOther);
    f32 fVar6;
    f32 fVar4;

    if (dotVal + 1.0f  > 1e-5f) {
        if (1.0f - dotVal > 1e-5f) {
            fVar4 = acosf(dotVal);
            f32 dotSinf = sinf(dotVal);
            fVar6 = sinf((1.0f - arg1) * fVar4);
            fVar6 /= dotSinf;
            fVar4 = sinf(dotVal * fVar4);
            dotVal = fVar4 / dotSinf;
        } else {
            fVar6 = 1.0f - arg1;
        }
        return *this + (((*this * dotVal)) * fVar6);
    }
    Vector3 vec1 = Vector3(-rOther.y, rOther.x, 0.0f);

    if (arg1 < 0.5f) {
        fVar4 = sinf(1.5707964f * -(2.0f * fVar6 - 1.0f));
        fVar6 = sinf(1.5707964f * 2.0f * fVar6);
        return *this + (((*this * fVar4)) * fVar6);
    }
    fVar6 = arg1 - 0.5f;
    fVar6 = sinf(1.5707964f  * -(2.0f * dotVal - 1.0f));
    fVar4 = sinf(1.5707964f *  2.0f * dotVal);
    return *this + (((*this * fVar4)) * fVar6);
}

void Vector3::reflect(const Vector3& rOther, f32 arg1) {
    f32 dotVal = dot(rOther);
    if (std::fabs(dotVal) > 1e-5f) {
        *this += (rOther *  ((-1.0f - arg1) * dotVal));
    }
}

void Vector3::scale(const Vector3& rOther) {
    x *= rOther.x;
    y *= rOther.y;
    z *= rOther.z;
}

//https://decomp.me/scratch/a4eWt
void Vector3::getScaled(const Vector3& rOther) const {
    const_cast<Vector3*>(this)->scale(rOther);
}

void Vector3::operator-=(const Vector3& rOther) {
    x -= rOther.x;
    y -= rOther.y;
    z -= rOther.z;
}
