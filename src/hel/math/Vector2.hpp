#ifndef HEL_MATH_VECTOR2_HPP
#define HEL_MATH_VECTOR2_HPP

#include <nw4r/math.h>

namespace hel { namespace math {
    class Vector2 {
    public:
        Vector2() { }
        Vector2(float _x, float _y)
            : x(_x)
            , y(_y)
        { }

        ~Vector2() { }

        void operator=(const Vector2& rOther);
        inline Vector2 operator+(const Vector2& rOther) const;
        inline Vector2 operator*(float scalar) const;

        /* 0x0 */ float x;
        /* 0x4 */ float y;
    };

    // function definitions
    inline Vector2 Vector2::operator+(const Vector2& rOther) const {
        Vector2 v;
        v.x = x + rOther.x;
        v.y = y + rOther.y;
        return v;
    }

    inline Vector2 Vector2::operator*(float scalar) const {
        Vector2 v;
        v.x = x * scalar;
        v.y = y * scalar;
        return v;
    }
} // math

} // hel

#endif
