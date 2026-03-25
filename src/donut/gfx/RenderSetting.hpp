#ifndef DONUT_GFX_RENDERSETTING_HPP
#define DONUT_GFX_RENDERSETTING_HPP

#include "gfx/IDrawer.hpp"

namespace gfx {

class RenderSetting {
public:
    void render(IDrawer& rDrawer, void* pTarget);
};

}

#endif
