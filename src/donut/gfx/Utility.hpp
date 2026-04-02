#ifndef DONUT_GFX_UTLITY_HPP
#define DONUT_GFX_UTLITY_HPP

#include <donut/gfx/RenderSetting.hpp>

namespace gfx {

namespace Utility {
    void SetupGXForLayout2D(f32 nearClip, f32 farClip);
    void SetupGXForLayout2D(f32 width, f32 height, f32 nearClip, f32 farClip);
    void SetupGXForScreen2D(f32 nearClip, f32 farClip);
    void SetupGXForScreen2D(f32 width, f32 height, f32 nearClip, f32 farClip);
    void SetViewPort(f32 left, f32 top, f32 right, f32 bottom);
    u32 CurrentGameWidth();
    u32 CurrentGameHeight();
    void SetZBufferRange(f32 min, f32 max);
    void ClearZBuffer(f32 zOffset);
    void SetGXStateDirty();
    void SetDimmingEnable(bool dimmingEnabled);
    void SetRenderType(RenderSetting::Type type);

}
}

#endif
