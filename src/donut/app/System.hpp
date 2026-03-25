#ifndef DONUT_APP_SYSTEM_HPP
#define DONUT_APP_SYSTEM_HPP

#include "gfx/GXFifoMemoryManager.hpp"
#include "gfx/RenderSetting.hpp"
#include "gfx/XFBManager.hpp"

namespace app {

class System {
public:
    gfx::GXFifoMemoryManager& gfxFifoMemoryManager();
    gfx::XFBManager& xfbManager();
    gfx::RenderSetting& renderSetting();
};


}

#endif
