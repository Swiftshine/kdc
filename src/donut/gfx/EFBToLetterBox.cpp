#pragma peephole off
#include <donut/gfx/EFBToLetterBox.hpp>
#include <donut/gfx/VISetting.hpp>
#include <donut/gfx/Utility.hpp>
#include <donut/gfx/RenderSetting.hpp>
#include <donut/mem/Memory.hpp>
#include <donut/gfx/GameScreen.hpp>
#include <nw4r/ut/ut_algorithm.h>
#include <hel/math/Matrix34.hpp>
#include <hel/math/Matrix44.hpp>
#include <hel/math/Vector3.hpp>
#include <donut/gfx/EasyRender3D.hpp>

namespace gfx {
    namespace {
        void t_capture(const TexBuffer& rTexBuffer, u16 texWidth, u16 texHeight, u16 yStart, bool arg5) {
            Utility::SetGXStateDirty();
            GXColor black = {0,0,0, 255};
            GXSetCopyClear(black, 0);
            GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
            GXSetColorUpdate(GX_TRUE);
            GXSetAlphaUpdate(GX_TRUE);
            GXSetTexCopySrc(0, yStart, texWidth, texHeight);
            GXSetTexCopyDst(texWidth, texHeight, GX_TF_RGBA8, GX_FALSE);
            u32 blockData = (u32)rTexBuffer.block().startAddress();

            if (arg5) {
                //This keeps showing up, could be an inline
                blockData += (u16)((VISetting::Instance->mRenderModeObj->fbWidth + 0xF) & 0xFFFFFFF0) * 228 << 2;
            }

            GXCopyTex((void*)blockData, GX_TRUE);
            GXInvalidateTexAll();
            GXPixModeSync();
            GXTexModeSync();
        }
    }

    EFBToLetterBox::EFBToLetterBox(GameScreen& rGameScreen)
        : mGameScreen(&rGameScreen)
        , mBuffer(mem::Memory::Instance->mem2FixHeap(), 640,
        456, GX_TF_RGBA8)
    {
    }
    EFBToLetterBox::~EFBToLetterBox() {}

    //TODO: Create a pch for nw4r::ut::RoundUp
    //https://decomp.me/scratch/KVDLi
    void EFBToLetterBox::draw() {
        if (VISetting::Instance->mIsWidescreen) {
                return;
        }
        if (mGameScreen->getScreenType() == GameScreen::SCREEN_TYPE_WIDESCREEN) {
            return;
        }

        GXRenderModeObj* renderObj;
        u32 renderWidth;
        u32 renderHeight;

        VISetting* setting = VISetting::Instance.object();
        switch (RenderSetting::Instance->m_8) {
            case 0:
            renderObj = setting->mRenderModeObj;
            renderHeight = nw4r::ut::RoundUp<u16>(renderObj->xfbHeight,4);
            renderWidth = nw4r::ut::RoundUp<u16>(renderObj->fbWidth,4);
            t_capture(mBuffer, renderWidth, renderHeight, 0, false);
            break;
            case 1:
            renderObj = setting->mRenderModeObj;
            renderHeight = nw4r::ut::RoundUp<u16>(renderObj->efbHeight,4);
            renderWidth = nw4r::ut::RoundUp<u16>(renderObj->fbWidth,4);
            t_capture(mBuffer, renderWidth, renderHeight, 0, false);
            break;
            case 2:
            renderObj = setting->mRenderModeObj;
            renderWidth = nw4r::ut::RoundUp<u16>(renderObj->fbWidth,4);
            t_capture(mBuffer, renderWidth, 228, 2, true);
            break;
        }
        hel::math::Matrix44 orthoMtx = hel::math::Matrix44::CreateOrtho(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
        EasyRender3D::SetupGX(orthoMtx, false);
        hel::math::Vector3 vec(hel::math::Vector3::BASIS_Z);
        vec.x *= -1.0f;
        vec.y *= -1.0f;
        vec.z *= -1.0f;
        hel::math::Vector3 tempLoadIG(vec);

        hel::math::Matrix34 viewMtx;
        viewMtx.CreateLookAt(hel::math::Vector3::ZERO, hel::math::Vector3::BASIS_Y, tempLoadIG);
        EasyRender3D::SetViewMtx(viewMtx);

        GXTexObj texObj;
        GXInitTexObj(&texObj, mBuffer.block().startAddress(), mBuffer.width(),
        mBuffer.height(), mBuffer.format(), GX_CLAMP,GX_CLAMP,0);
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f,
            0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        GXSetViewport(0.0f, 61.0f, 640.0f, 334.0f, 0.0f, 1.0f);
        GXSetColorUpdate(GX_TRUE);
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetAlphaCompare(GX_NEVER, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        GXSetNumChans(0);
        GXSetCullMode(GX_CULL_NONE);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        Mtx mtx;
        PSMTXIdentity(mtx);
        GXLoadPosMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-1.0f, 1.0f, -0.5f);
        GXPosition3f32(0.0f, 0.0f, 1.0f);
        GXPosition3f32(1.0f, -0.5f, 1.0f);
        GXPosition3f32(0.0f, 1.0f, -1.0f);
        GXPosition3f32(-0.5f, 1.0f, 1.0f);
        GXPosition3f32(-1.0f, -1.0f, -0.5f);
        GXPosition2f32(0.0f, 1.0f);
    }

    //NOTE: All functions below are code merged into others. Refer to the header for more details
    TexBuffer EFBToLetterBox::texBuffer() {
        return mBuffer;
    }
}
