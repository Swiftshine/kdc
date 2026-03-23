#ifndef HEL_MATH_MATRIX34_HPP
#define HEL_MATH_MATRIX34_HPP

#include <nw4r/math.h>
#include <hel/math/Matrix44.hpp>

namespace hel  { namespace math {
    class Direction3;
    class Vector3;

    class Matrix34 {
    public:
        Matrix34();
        Matrix34(const Mtx);
        Matrix34(const Direction3&, const Vector3&);

        void CreateTrans(const Vector3& rTrans);
        void CreateScale(const Vector3& rScale);
        void CreateRotAxisRad(const Vector3& rAxis, f32 radians);
        void CreateRotAxisDeg(const Vector3& rAxis, f32 degrees);
        void CreateRotXYZRad(const Vector3& rRotation);
        void CreateRotXYZDeg(const Vector3& rRotation);
        void CreateLookAt(const Vector3& rPosition, const Vector3& rUp, const Vector3& rTarget);
        void mtxInverse(const Mtx arg1, Mtx arg2) const;
        Matrix44 toMatrix44() const;

        nw4r::math::MTX34 mBaseMtx;
    };

} //namespace math

} //namespace hel
#endif
