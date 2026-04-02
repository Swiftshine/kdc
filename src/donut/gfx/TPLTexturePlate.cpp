#pragma peephole off
#include <hel/math/Vector2.hpp>
#include <donut/gfx/TPLTexturePlate.hpp>
#include <donut/gfx/Utility.hpp>
#include <donut/gfx/VISetting.hpp>

using gfx::TPLTexturePlate;

TPLTexturePlate::TPLTexturePlate(void* pArg1)
    : mTPLTexture(pArg1)
    , mPos()
    , mAlpha(0)
    , mInited(false)
{
    init();
}

void TPLTexturePlate::init() {
    mTexObj = mTPLTexture.texObj();

    m_4C.left = 0.5f * -GXGetTexObjWidth(&mTexObj);
    m_4C.top = 0.5f * GXGetTexObjHeight(&mTexObj);
    m_4C.right = 0.5f * GXGetTexObjWidth(&mTexObj);
    m_4C.bottom = 0.5f * -GXGetTexObjHeight(&mTexObj);
    PSMTXIdentity(mPos);
    mAlpha = 255;
    mInited = true;
}

//The 0xFF may be a cast but idk what cast if so
void TPLTexturePlate::setAlpha(u8 alpha) {
    mAlpha = alpha & 0xFF;
}

void TPLTexturePlate::drawForHomeButtonIcon() const {
    if (mInited) {
        gfx::Utility::SetupGXForLayout2D(gfx::VISetting::Instance->mScreenWidth,
            gfx::VISetting::Instance->mScreenHeight, 0.0f, 1.0f);

        drawCore();
    }
}

void TPLTexturePlate::drawCore() const {
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXLoadTexObj(&mTexObj, GX_TEXMAP0);
    setupTevRenderModePlane();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXLoadPosMtxImm(mPos, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(m_4C.left, m_4C.top);
    GXPosition2f32(0.0f, 0.0f);
    GXPosition2f32(m_4C.right, m_4C.top);
    GXPosition2f32(1.0f, 0.0f);
    GXPosition2f32(m_4C.right, m_4C.bottom);
    GXPosition2f32(1.0f, 1.0f);
    GXPosition2f32(m_4C.left, m_4C.bottom);
    GXPosition2f32(0.0f, 1.0f);
    GXTexModeSync();
}

void TPLTexturePlate::setupTevRenderModePlane() const {
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXColor color = {0, 0,0 ,mAlpha};
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    //Why tho
    GXColor color2 = color;
    GXSetChanAmbColor(GX_COLOR0A0, color2);
    GXSetChanMatColor(GX_COLOR0A0, color2);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

void TPLTexturePlate::setPos(const hel::math::Vector2& rPosition) {
    PSMTXTrans(mPos, rPosition.x, rPosition.y, 0.0f);
}
