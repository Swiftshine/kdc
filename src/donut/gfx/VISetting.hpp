#ifndef DONUT_GFX_VI_SETTING_HPP
#define DONUT_GFX_VI_SETTING_HPP

#include <hel/common/ExplicitSingleton.hpp>
#include <revolution/GX.h>


namespace gfx {

    struct VISettingPreset {
        /* 0x0 */ GXRenderModeObj mRenderModeObj;
        /* 0x3C */ u16 mScreenWidth;
        /* 0x3E */ u16 mScreenHeight;
        /* 0x40 */ bool mIsWidescreen;
    };

    class VISetting : public hel::common::ExplicitSingleton<VISetting> {
    public:
        DECL_EXPLICIT_SINGLETON(VISetting);
        VISetting();
        ~VISetting();

        u32 recommendRenderModeNo() const;
        void set(u32);
        void set(const GXRenderModeObj& rRenderModeObj, u16 screenWidth, u16 screenHeight, bool isWidescreen);
        VISettingPreset* rmode(u32 mode) const;
        void setDimming(bool dimming);
        bool getDimming() const;

        /* 0x0 */ GXRenderModeObj* mRenderModeObj;
        /* 0x4 */ u16 mScreenWidth;
        /* 0x6 */ u16 mScreenHeight;
        /* 0x8 */ bool mIsWidescreen;
        /* 0xC */ u32 mMode;
        /* 0x10 */ bool mDimming;
    };
}

#endif
