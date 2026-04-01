#ifndef HEL_MATH_POINT2_HPP
#define HEL_MATH_POINT2_HPP

#include <nw4r/math.h>
namespace hel { namespace math {
    class Point2 {
    public:

        static Point2 ORIGIN;

        //NOTE: Is merged into hel::math::Vector2::set(float, float)
        Point2(f32 _x, f32 _y);
        //NOTE: Is merged into mint_wrapNative_helper<hel::math::Vector2>::mint_wrapNative_helper(hel::math::Vector2)
        Point2(const Point2&);

        //NOTE: Is merged into effect::detail::RequestArgOption::scale() const
        f32 y() const {
            return mY;
        }

        //NOTE: Is merged into nw4r::ef::HandleBase::HandleBase(const nw4r::ef::HandleBase&)
        void operator=(const Point2& rOther);

        /* 0x0 */ f32 mX;
        /* 0x4 */ f32 mY;
    };
} // math

} // hel

#endif
