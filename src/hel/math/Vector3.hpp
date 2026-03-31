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

        //TODO: Make this use LWZ and STW
        Vector3(const Vector3& rOther)
        : x(rOther.x)
        , y(rOther.y)
        , z(rOther.z)
        { }

        //TODO: Is this compiler generated?
        Vector3();

        void operator=(const Vector3& rOther);

        //https://decomp.me/scratch/IP61P
        Vector3 operator+(const Vector3& rOther) const {
            Vector3 stack(*this);

            stack.x = stack.x + rOther.x;
            stack.y = stack.y + rOther.y;
            stack.z = stack.z + rOther.z;
            Vector3 stack2(stack);
            return stack2;
        }
        void operator+=(const Vector3& rOther);
        void operator-=(const Vector3& rOther);
        void operator*=(f32 scalar);
        void operator/=(f32 scalar);
        Vector3 operator*(float scalar) const;

        f32 length() const;
        Vector3 cross(const Vector3& rOther) const;
        f32 normalize();
        f32 permittedNormalize();
        Vector3 normalizedCross(const Vector3& rOther) const;
        Vector3 permittedNormalizedCross(const Vector3& rOther) const;
        f32 setLength(f32);
        f32 cos(const Vector3& rOther) const;
        f32 dot(const Vector3& rOther) const;

        bool isZero() const {
            return x == ZERO.x && y == ZERO.y && z == ZERO.z;
        }
        //branches to isZero due to code merging lol
        bool isZeroStrict() const;
        void rotate(const Vector3& rAxis, f32 angle);
        void rotate(AxisKind axis, f32 angle);
        Vector3 slerp(const Vector3& rOther, f32 arg1) const;
        void reflect(const Vector3& rOther, f32 arg1);
        void scale(const Vector3& rOther);
        void getScaled(const Vector3& rOther) const;

        /* 0x0 */ f32 x;
        /* 0x4 */ f32 y;
        /* 0x8 */ f32 z;
    };
} // math

} // hel

#endif
