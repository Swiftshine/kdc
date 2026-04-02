#ifndef NREL_ORTHO_CAMERA_SETTING_HPP
#define NREL_ORTHO_CAMERA_SETTING_HPP

#include <types.h>

namespace nrel { namespace ezrender {
    class OrthoCameraSetting {
    public:
        static OrthoCameraSetting create(f32, f32, f32, f32, f32, f32);

        /* 0x00 */ f32 mLeft;
        /* 0x04 */ f32 mTop;
        /* 0x08 */ f32 mRight;
        /* 0x0C */ f32 mBottom;
        /* 0x10 */ f32 mNearClip;
        /* 0x14 */ f32 mFarClip;
    };

}; // ezrender

}; //nrel

#endif
