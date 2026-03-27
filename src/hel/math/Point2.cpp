#include <hel/math/Point2.hpp>

using hel::math::Point2;

Point2 Point2::ORIGIN = Point2(0.0f, 0.0f);

Point2::Point2(f32 _x, f32 _y)
    : mX(_x)
    , mY(_y)
{ }
