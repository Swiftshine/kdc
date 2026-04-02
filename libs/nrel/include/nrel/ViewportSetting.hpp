#ifndef NREL_VIEWPORT_SETTING_HPP
#define NREL_VIEWPORT_SETTING_HPP

#include <types.h>

namespace nrel { namespace ezrender {
    class ViewportSetting {
    public:
        //NOTE: Merged into nrel::ezrender::OrthoCameraSetting::create(f32, f32, f32, f32, f32, f32)
        static ViewportSetting create(f32, f32, f32, f32, f32, f32);

        /* 0x00 */ f32 mOriginX;
        /* 0x04 */ f32 mOriginY;
        /* 0x08 */ f32 mSizeX;
        /* 0x0C */ f32 mSizeY;
        /* 0x10 */ f32 mNearClip;
        /* 0x14 */ f32 mFarClip;
    };

}; // ezrender

}; //nrel

#endif
