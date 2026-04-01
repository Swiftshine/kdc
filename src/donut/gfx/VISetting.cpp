#pragma peephole off
#include <donut/gfx/VISetting.hpp>
#include <donut/gfx/RenderSetting.hpp>
#include <revolution/VI.h>
#include <revolution/SC.h>

namespace gfx {
    namespace {
        const VISettingPreset NtscInt4x3 = {
            {
                0,
                640,
                456,
                456,
                25,
                12,
                670,
                456,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset NtscInt4x3AA = {
            {
                0,
                640,
                230,
                456,
                25,
                12,
                670,
                456,
                1,
                GX_FALSE,
                GX_TRUE,
                {
                    {3,2},
                    {9,6},
                    {3,10},
                    {3,2},
                    {9,6},
                    {3,10},
                    {9,2},
                    {3,6},
                    {9,10},
                    {9,2},
                    {3,6},
                    {9,10},
                },
                {
                    4,
                    8,
                    12,
                    16,
                    12,
                    8,
                    4,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset NtscProg4x3 = {
            {
                2,
                640,
                456,
                456,
                25,
                12,
                670,
                456,
                0,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    0,
                    0,
                    21,
                    22,
                    21,
                    0,
                    0,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset NtscProg4x3AA = {
            {
                2,
                640,
                230,
                456,
                25,
                12,
                670,
                456,
                0,
                GX_FALSE,
                GX_TRUE,
                {
                    {3,2},
                    {9,6},
                    {3,10},
                    {3,2},
                    {9,6},
                    {3,10},
                    {9,2},
                    {3,6},
                    {9,10},
                    {9,2},
                    {3,6},
                    {9,10},
                },
                {
                    4,
                    8,
                    12,
                    16,
                    12,
                    8,
                    4,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset Pal50Int4x3 = {
            {
                4,
                640,
                456,
                542,
                27,
                16,
                666,
                542,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset Pal60Int4x3 = {
            {
                20,
                640,
                456,
                456,
                25,
                12,
                670,
                456,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset Pal60Prog4x3 = {
            {
                22,
                640,
                456,
                456,
                25,
                12,
                670,
                456,
                0,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    0,
                    0,
                    21,
                    22,
                    21,
                    0,
                    0,
                }
            },
            608,
            456,
            false
        };

        const VISettingPreset NtscInt16x9 = {
            {
                0,
                640,
                456,
                456,
                17,
                12,
                686,
                456,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset NtscInt16x9AA = {
            {
                0,
                640,
                230,
                456,
                17,
                12,
                686,
                456,
                1,
                GX_FALSE,
                GX_TRUE,
                {
                    {3,2},
                    {9,6},
                    {3,10},
                    {3,2},
                    {9,6},
                    {3,10},
                    {9,2},
                    {3,6},
                    {9,10},
                    {9,2},
                    {3,6},
                    {9,10},
                },
                {
                    4,
                    8,
                    12,
                    16,
                    12,
                    8,
                    4,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset NtscProg16x9 = {
            {
                2,
                640,
                456,
                456,
                17,
                12,
                686,
                456,
                0,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    0,
                    0,
                    21,
                    22,
                    21,
                    0,
                    0,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset NtscProg16x9AA = {
            {
                2,
                640,
                230,
                456,
                17,
                12,
                686,
                456,
                0,
                GX_FALSE,
                GX_TRUE,
                {
                    {3,2},
                    {9,6},
                    {3,10},
                    {3,2},
                    {9,6},
                    {3,10},
                    {9,2},
                    {3,6},
                    {9,10},
                    {9,2},
                    {3,6},
                    {9,10},
                },
                {
                    4,
                    8,
                    12,
                    16,
                    12,
                    8,
                    4,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset Pal50Int16x9 = {
            {
                4,
                640,
                456,
                542,
                19,
                16,
                682,
                542,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset Pal60Int16x9 = {
            {
                20,
                640,
                456,
                456,
                17,
                12,
                686,
                456,
                1,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    7,
                    7,
                    12,
                    12,
                    12,
                    7,
                    7,
                }
            },
            832,
            456,
            true
        };

        const VISettingPreset Pal60Prog16x9 = {
            {
                22,
                640,
                456,
                456,
                17,
                12,
                686,
                456,
                0,
                GX_FALSE,
                GX_FALSE,
                {
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                    {6,6},
                },
                {
                    0,
                    0,
                    21,
                    22,
                    21,
                    0,
                    0,
                }
            },
            832,
            456,
            true
        };

        //Weird way in order to get this to show up in data
        VISettingPreset* StandardRenderModeSets[14] = {
            (VISettingPreset*)&NtscInt4x3,
            (VISettingPreset*)&NtscInt4x3AA,
            (VISettingPreset*)&NtscProg4x3,
            (VISettingPreset*)&NtscProg4x3AA,
            (VISettingPreset*)&Pal50Int4x3,
            (VISettingPreset*)&Pal60Int4x3,
            (VISettingPreset*)&Pal60Prog4x3,
            (VISettingPreset*)&NtscInt16x9,
            (VISettingPreset*)&NtscInt16x9AA,
            (VISettingPreset*)&NtscProg16x9,
            (VISettingPreset*)&NtscProg16x9AA,
            (VISettingPreset*)&Pal50Int16x9,
            (VISettingPreset*)&Pal60Int16x9,
            (VISettingPreset*)&Pal60Prog16x9,
        };
    }

    VISetting::VISetting()
        : mRenderModeObj(nullptr)
        , mScreenWidth(0)
        , mScreenHeight(0)
        , mIsWidescreen(0)
        , mMode(0)
        , mDimming(1)
    {
        Instance = this;
        set(14);
    }

    VISetting::~VISetting() {
        Instance = nullptr;
    }

    //https://decomp.me/scratch/z9zxm
    u32 VISetting::recommendRenderModeNo() const {
        u32 tvFormat =tvFormat = VIGetTvFormat();

        while (SCCheckStatus() != 0) { }

        bool progressiveMode = SCGetProgressiveMode() == 1;
        bool euRGBMode = SCGetEuRgb60Mode() == 1;
        bool aspectRatio = SCGetAspectRatio() == 0;
        bool DTVstatus = VIGetDTVStatus() == 1;
        bool bVar1 = false;
        if (tvFormat != 1 && tvFormat != 5) {
            bVar1 = true;
        }
        if (DTVstatus && progressiveMode) {
            if (bVar1) {
                if (aspectRatio) {
                    return 2;
                } else {
                    return 9;
                }
            } else {
                if (aspectRatio) {
                    return 6;
                }
                return 13;
            }
        } else {
            if (bVar1) {
                if (aspectRatio) {
                    return 0;
                } else {
                    return 7;
                }
            } else {
                if (euRGBMode) {
                    if (aspectRatio) {
                        return 5;
                    }
                    return 12;
                } else {
                    if (aspectRatio) {
                        return 4;
                    }
                }
                return 11;
            }
        }
    }

    void VISetting::set(u32 mode) {
        if (mode == 14) {
            mode = recommendRenderModeNo();
        }

        if (gfx::RenderSetting::Instance != nullptr) {
            if (gfx::RenderSetting::Instance->mType == gfx::RenderSetting::TYPE_2) {
                switch (mode) {
                    case 0:
                        mode = 1;
                        break;
                    case 2:
                        mode = 3;
                        break;
                    case 7:
                        mode = 8;
                        break;
                    case 9:
                        mode = 10;
                        break;
                }
            } else {
                switch(mode) {
                    case 1:
                        mode = 0;
                        break;
                    case 3:
                        mode = 2;
                        break;
                    case 8:
                        mode = 7;
                        break;
                    case 10:
                        mode = 9;
                        break;
                }
            }
        }

        VISettingPreset* preset = StandardRenderModeSets[mode];
        set(preset->mRenderModeObj, preset->mScreenWidth, preset->mScreenHeight, preset->mIsWidescreen);
        mMode = mode;
    }

    void VISetting::set(const GXRenderModeObj& rRenderModeObj, u16 screenWidth, u16 screenHeight, bool isWidescreen) {
        if (&rRenderModeObj != mRenderModeObj) {
            mRenderModeObj = (GXRenderModeObj*)&rRenderModeObj;
            mScreenWidth = screenWidth;
            mScreenHeight = screenHeight;
            mIsWidescreen = isWidescreen;
            VISetBlack(TRUE);
            VIConfigure(&rRenderModeObj);
            VIFlush();
            GXSetDispCopySrc(0,0, rRenderModeObj.fbWidth, rRenderModeObj.efbHeight);
            GXSetDispCopyDst(rRenderModeObj.fbWidth, rRenderModeObj.xfbHeight);
            GXSetDispCopyYScale(1.0f);
            GXSetDispCopyGamma(0);
            VIWaitForRetrace();
            VIWaitForRetrace();
        }
    }

    GXRenderModeObj* VISetting::rmode(u32 mode) const {
        return &StandardRenderModeSets[mode]->mRenderModeObj;
    }

    void VISetting::setDimming(bool dimming) {
        mDimming = dimming;
        VIEnableDimming(dimming);
    }

    bool VISetting::getDimming() const {
        return mDimming;
    }
}
