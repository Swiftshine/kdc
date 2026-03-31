#pragma peephole off
#include <nw4r/g3d/g3d_state.h>
#include <donut/gfx/RenderSetting.hpp>
#include <donut/gfx/VISetting.hpp>
#include <donut/gfx/Utility.hpp>
#include <nrel/OrthoCameraSetting.hpp>

namespace {
    static const f32 VIEWPORT_NEAR = 0;

    //I don't even know if the data in this struct is used, just the overall garbage data
    struct garbageStruct {
        STRUCT_FILL(0xA00);
    };

    garbageStruct garbage;

    void t_setCopyClear() {
        GXColor copyClearColor = {0, 0, 0, 255};
        GXSetCopyClear(copyClearColor, 0xFFFFFF);
    }
}

namespace gfx {
    RenderSetting::RenderSetting()
        : mVISetting(VISetting::Instance->object())
        , mType(TYPE_0)
        , m_8(0)
        , mDirty(true)
        , m_D(false)
        , mViewportRect(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight)
        , mScissor(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight)
        , m_30(0)
    {
        Instance = this;
    }

    RenderSetting::Rect::Rect(f32 left, f32 top, f32 right, f32 bottom)
        : mLeft(left)
        , mTop(top)
        , mRight(right)
        , mBottom(bottom)
    { }

    RenderSetting::~RenderSetting() {
        Instance = nullptr;
    }

    //https://decomp.me/scratch/xM91a
    GXRenderModeObj* RenderSetting::rmode() const {
        u32 mTypeU32 = mType;
        u32 mMode = mVISetting->mMode;

        switch (mTypeU32) {
            case TYPE_2:
                switch (mMode) {
                    case 0:
                        return mVISetting->rmode(1);
                    case 2:
                        return mVISetting->rmode(3);
                    case 7:
                        return mVISetting->rmode(8);
                    case 9:
                        return mVISetting->rmode(10);
                }
                break;
            case TYPE_0:
            case TYPE_1:
                switch (mMode) {
                    case 1:
                        return mVISetting->rmode(0);
                    case 3:
                        return mVISetting->rmode(2);
                    case 8:
                        return mVISetting->rmode(7);
                    case 10:
                        return mVISetting->rmode(9);
                }
            break;
        }
        return mVISetting->mRenderModeObj;
    }

    void RenderSetting::render(IDrawer& rDrawer, void* pTarget) {
        nw4r::g3d::G3DState::SetRenderModeObj(*rmode());
        Rect viewport2 = Rect(0.0f, 0.0f, rmode()->fbWidth,  rmode()->xfbHeight);
        mViewportRect.mLeft = viewport2.mLeft;
        mViewportRect.mTop = viewport2.mTop;
        mViewportRect.mRight = viewport2.mRight;
        mViewportRect.mBottom = viewport2.mBottom;
        GXSetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
            mViewportRect.mBottom, VIEWPORT_NEAR, 1.0f);
        GXInvalidateVtxCache();
        GXInvalidateTexAll();

        if (mDirty) {
            mDirty = false;
            reset();
            renderImpl(rDrawer, pTarget);
        }
        renderImpl(rDrawer, pTarget);
    }

    //https://decomp.me/scratch/pZtcK
    void RenderSetting::renderImpl(IDrawer& rDrawer, void* pTarget) {
        switch ((u32)mType) {
            case TYPE_0:
            case TYPE_1:
                m_8 = 0;
                beginNormal();
                rDrawer.drawerExecDraw();
                if (m_30 != nullptr) {
                    m_30(m_8);
                }
                endNormal(pTarget);
                break;
            case TYPE_2:
                m_8  = 1;
                beginAATopHalf();
                rDrawer.drawerExecDraw();
                if (m_30 != nullptr) {
                    m_30(m_8);
                }
                endAATopHalf(pTarget);
                m_8  = 2;
                beginAABottomHalf();
                rDrawer.drawerExecDraw();
                if (m_30 != nullptr) {
                    m_30(m_8);
                }
                endAABottomHalf(pTarget);
                break;
        }
    }

    void RenderSetting::type(Type type) {
        if (type == mType) {
            return;
        }
        mType = type;
        dirty();
    }

    void RenderSetting::setupG3DCamera(nw4r::g3d::Camera camera) {
        if (m_D) {
            camera.SetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
                mViewportRect.mBottom);
            camera.SetScissor(mScissor.mLeft, mScissor.mTop, mScissor.mRight, mScissor.mBottom);
            camera.SetScissorBoxOffset(0, 0);
            return;
        }
        switch (m_8) {
            case 0:
                camera.SetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
                    mViewportRect.mBottom);
                camera.SetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
                camera.SetScissorBoxOffset(0, 0);
                break;
            case 1:
                camera.SetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
                    mViewportRect.mBottom);
                camera.SetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
                camera.SetScissorBoxOffset(0, 0);
                break;
            case 2:
                camera.SetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
                    mViewportRect.mBottom);
                camera.SetScissor(0, 226, rmode()->fbWidth, rmode()->efbHeight);
                camera.SetScissorBoxOffset(0, 226);
                break;
        }
    }

    void RenderSetting::setViewportValue(f32 left, f32 top, f32 right, f32 bottom) {
        mScissor.mLeft = left;
        mViewportRect.mLeft = left;
        mScissor.mTop = top;
        mViewportRect.mTop = top;
        mScissor.mRight = right;
        mViewportRect.mRight = right;
        mScissor.mBottom = bottom;
        mViewportRect.mBottom = bottom;
        GXSetViewport(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
            mViewportRect.mBottom, VIEWPORT_NEAR, 1.0f);
        GXSetScissor(mScissor.mLeft, mScissor.mTop, mScissor.mRight, mScissor.mBottom);
        m_D = true;
    }

    //https://decomp.me/scratch/mEQFW
    nrel::ezrender::OrthoCameraSetting* RenderSetting::nrelViewportSetting() const {
        return nrel::ezrender::OrthoCameraSetting::create(mViewportRect.mLeft, mViewportRect.mTop, mViewportRect.mRight,
            mViewportRect.mBottom, VIEWPORT_NEAR, 1.0f);
    }

    void RenderSetting::reset() {
        switch (mType) {
            case 0:
                GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
                GXSetCopyFilter(GX_FALSE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
                break;
            case 1:
                GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
                GXSetCopyFilter(GX_FALSE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
                break;
            case 2:
                GXSetPixelFmt(GX_PF_RGBA565_Z16, GX_ZC_FAR);
                GXSetCopyFilter(GX_TRUE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
                break;
        }
        Utility::SetZBufferRange(0.0f, 1.0f);
    }

    void RenderSetting::beginNormal() {
        GXSetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
        GXSetScissorBoxOffset(0, 0);
    }

    void RenderSetting::beginAABottomHalf() {
        GXSetScissor(0, 226, rmode()->fbWidth, rmode()->efbHeight);
        GXSetScissorBoxOffset(0, 226);
    }

    void RenderSetting::endNormal(void* pTarget) {
        t_setCopyClear();
        GXSetCopyClamp(GX_CLAMP_ALL);
        u16 height = rmode()->efbHeight;
        u16 width = rmode()->fbWidth;

        GXSetDispCopySrc(0, 0, width, height);
        height = rmode()->xfbHeight;
        width = rmode()->fbWidth;
        GXSetDispCopyDst(width, height);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXCopyDisp(pTarget, GX_TRUE);
    }

    void RenderSetting::endAATopHalf(void* pTarget) {
        t_setCopyClear();
        GXSetCopyClamp(GX_CLAMP_ALL);
        u16 height = rmode()->efbHeight;
        u16 width = rmode()->fbWidth;

        GXSetDispCopySrc(0, 0, width, height);
        height = rmode()->efbHeight;
        width = rmode()->fbWidth;
        GXSetDispCopyDst(width, height);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXCopyDisp(pTarget, GX_TRUE);
    }

    void RenderSetting::endAABottomHalf(void* pTarget) {
        t_setCopyClear();
        GXSetCopyClamp(GX_CLAMP_BOTTOM);
        u16 height;
        u16 width = rmode()->fbWidth;

        GXSetDispCopySrc(0, 2, width, 228);
        height = rmode()->efbHeight;
        width = rmode()->fbWidth;
        GXSetDispCopyDst(width, height);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        //An abomination that is required for matching.
        //The `<< 1` and `& 0xFFFFFFF0` may be casts but idk
        u32 val = ((u32)(u16)((rmode()->fbWidth + 0xF) & 0xFFFFFFF0) * 228) << 1;

        GXCopyDisp((void *)((u32)pTarget + val), GX_TRUE);

        GXSetCopyClamp(GX_CLAMP_ALL);
        width = rmode()->fbWidth;
        GXSetDispCopySrc(0, 0, width, 2);
        GXCopyDisp(&garbage, GX_TRUE);
    }

    //NOTE: All functions below are code merged into others. Refer to the header for more details

    void RenderSetting::beginAATopHalf() {
        GXSetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
        GXSetScissorBoxOffset(0, 0);
    }

    void RenderSetting::dirty() {
        mDirty = true;
    }

}
