#ifndef DONUT_GFX_RENDERSETTING_HPP
#define DONUT_GFX_RENDERSETTING_HPP

#include <nw4r/g3d/g3d_camera.h>
#include <donut/gfx/IDrawer.hpp>
#include <hel/common/ExplicitSingleton.hpp>

namespace nrel { namespace ezrender {
    class OrthoCameraSetting;
}; };

namespace gfx {

struct VISettingPreset;
class VISetting;


class RenderSetting : public hel::common::ExplicitSingleton<RenderSetting> {
public:
    typedef void (*RenderSettingCallback)(s32 val);

    enum Type {
        TYPE_0,
        TYPE_1,
        TYPE_2,
    };

    class Rect {
    public:
        Rect(f32 left, f32 top, f32 right, f32 bottom);

        /* 0x0 */ f32 mLeft;
        /* 0x4 */ f32 mTop;
        /* 0x8 */ f32 mRight;
        /* 0xC */ f32 mBottom;
    };

    DECL_EXPLICIT_SINGLETON(RenderSetting);

    RenderSetting();
    ~RenderSetting();

    void render(IDrawer& rDrawer, void* pTarget);
    void renderImpl(IDrawer& rDrawer, void* pTarget);
    void beginNormal();
    void endNormal(void*);
    void beginAABottomHalf();
    void endAABottomHalf(void*);
    //NOTE: Merged into beginNormal
    void beginAATopHalf();
    void endAATopHalf(void*);
    void reset();
    GXRenderModeObj* rmode() const;
    void type(Type type);
    void setupG3DCamera(nw4r::g3d::Camera camera);
    void setViewportValue(f32, f32, f32, f32);
    nrel::ezrender::OrthoCameraSetting* nrelViewportSetting() const;
    //NOTE: Merged into gfx::GXFifoMemoryManager::setWriteEnable()
    void dirty();

    /* 0x00 */ VISetting* mVISetting;
    /* 0x04 */ Type mType;
    /* 0x08 */ s32 m_8;
    /* 0x0C */ bool mDirty;
    /* 0x0D */ bool m_D;
    /* 0x10 */ Rect mViewportRect;
    /* 0x20 */ Rect mScissor;
    /* 0x30 */ RenderSettingCallback m_30;
};

}

#endif
