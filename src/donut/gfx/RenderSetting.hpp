#ifndef DONUT_GFX_RENDERSETTING_HPP
#define DONUT_GFX_RENDERSETTING_HPP

#include "gfx/IDrawer.hpp"
#include <hel/common/ExplicitSingleton.hpp>

namespace gfx {
class VISetting;

class RenderSetting : public hel::common::ExplicitSingleton<RenderSetting> {
public:
    DECL_EXPLICIT_SINGLETON(RenderSetting);

    void render(IDrawer& rDrawer, void* pTarget);

    /* 0x0 */ VISetting* mVISetting;
    /* 0x4 */ s32 m_4;

};

}

#endif
