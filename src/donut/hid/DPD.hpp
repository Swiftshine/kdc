#ifndef DONUT_HID_DPD_HPP
#define DONUT_HID_DPD_HPP

#include <revolution/MTX.h>

namespace hid {
    class DPD {
    public:
        DPD();
        void update(f32 dist, const Vec2& rPos, const Vec2& rHori);

        /* 0x0 */ f32 mDist;
        /* 0x4 */ Vec2 mPos;
        /* 0xC */ Vec2 mHori;
    };
}
#endif
