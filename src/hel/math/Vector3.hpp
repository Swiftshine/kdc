#ifndef HEL_MATH_VECTOR3_HPP
#define HEL_MATH_VECTOR3_HPP

#include <nw4r/math.h>

namespace hel { namespace math {
    class Vector3 {
    public:
        Vector3(float, float, float);

        float x;
        float y;
        float z;
    };
} // math

} // hel

#endif
