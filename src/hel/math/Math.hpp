#ifndef HEL_MATH_MATH_HPP
#define HEL_MATH_MATH_HPP

#include <nw4r/math.h>

namespace hel {
namespace math {

namespace Math {
    template <typename T>
    const T Abs(T val) {
        return val < 0 ? -val : val;
    }

    f32 FloorF(f32 f);

    f32 CosF(f32 radians) {
        //these extra variables are required for no inlining in EasyRender3D
        f32 fidx = NW4R_MATH_RAD_TO_FIDX(radians);
        f32 cosFIDX = nw4r::math::CosFIdx(fidx);
        return cosFIDX;
    }

    f32 SinF(f32 radians) {
        //these extra variables are required for no inlining in EasyRender3D
        f32 fidx = NW4R_MATH_RAD_TO_FIDX(radians);
        f32 sinFIDX = nw4r::math::SinFIdx(fidx);
        return sinFIDX;
    }
}

}
}
#endif
