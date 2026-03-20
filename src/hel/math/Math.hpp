#ifndef HEL_MATH_MATH_HPP
#define HEL_MATH_MATH_HPP

namespace hel {
namespace math {

namespace Math {
    template <typename T>
    const T Abs(T val) {
        return val < 0 ? -val : val;
    }

    float FloorF(float f);
}

}
}
#endif
