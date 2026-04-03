#ifndef DONUT_HID_ACCEL_HPP
#define DONUT_HID_ACCEL_HPP

#include <revolution/MTX.h>

namespace hid {
    class Accel {
    public:
        Accel();

        //NOTE: Merged into hel::math::Vector3::operator=(const hel::math::Vector3&)
        void update(const Vec& accel);

        //NOTE: Merged into hel::math::Vector3::Vector3(const hel::math::Vector3&)
        Vec raw() const;

        /* 0x0 */ Vec mRaw;
    };
}
#endif
