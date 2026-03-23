#ifndef HEL_MATH_VECTOR3_HPP
#define HEL_MATH_VECTOR3_HPP

#include <nw4r/math.h>

namespace hel { namespace math {
    class Vector3 {
    public:

        enum AxisKind {
            AXIS_X,
            AXIS_Y,
            AXIS_Z,
        };

        static Vector3 ZERO;
        static Vector3 ALL_ONE;
        static Vector3 BASIS_X;
        static Vector3 BASIS_Y;
        static Vector3 BASIS_Z;

        //Gets merged into nw4r::math::VEC3::VEC3(float, float, float)
        Vector3(f32 _x, f32 _y, f32 _z);
        Vector3();

        void operator=(const Vector3& rOther);
        Vector3 operator+(const Vector3& rOther) const;
        void operator+=(const Vector3& rOther);
        void operator-=(const Vector3& rOther);
        void operator*=(f32 scalar);
        void operator/=(f32 scalar);
        Vector3 operator*(float scalar) const;

        f32 length() const;
        f32 cross(const Vector3& rOther) const;
        f32 normalize();
        f32 permittedNormalize();
        void normalizedCross(const Vector3& rOther) const;
        void permittedNormalizedCross(const Vector3& rOther) const;
        f32 setLength(f32);
        f32 cos(const Vector3& rOther) const;
        f32 dot(const Vector3& rOther) const;
        bool isZero() const;
        //branches to isZero due to code merging lol
        bool isZeroStrict() const;
        void rotate(const Vector3& rAxis, f32 angle);
        void rotate(AxisKind axis, f32 angle);
        Vector3 slerp(const Vector3& rOther, f32 arg1) const;
        void reflect(const Vector3& rOther, f32 arg1);
        void scale(const Vector3& rOther);
        void getScaled(const Vector3& rOther) const;

        f32 x;
        f32 y;
        f32 z;
    };
} // math

} // hel

#endif
