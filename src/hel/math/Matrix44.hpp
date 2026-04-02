#ifndef HEL_MATH_MATRIX44_HPP
#define HEL_MATH_MATRIX44_HPP

#include <nw4r/math.h>

namespace hel { namespace math {
    class Vector3;

    class Matrix44 {
    public:
        Matrix44();
        Matrix44(const nw4r::math::MTX44& rMtx);

        Matrix44 CreatePerspective(f32 FOV, f32 aspectRatio, f32 nearClip, f32 farClip);
        static Matrix44 CreateOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 nearClip, f32 farClip);
        nw4r::math::MTX44 mulMtx(const Matrix44&) const;
        Vector3 mulVec(const Vector3&) const;

        /* 0x0 */ nw4r::math::MTX44 mBaseMtx;
    };

} //namespace math

} //namespace hel
#endif
