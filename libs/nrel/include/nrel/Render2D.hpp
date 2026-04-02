#ifndef NREL_RENDER_2D_HPP
#define NREL_RENDER_2D_HPP

#include <nw4r/ut.h>

namespace nrel { namespace ezrender {
    class GXSettingFor2D;

    namespace Render2D {
        void renderRect(const nw4r::ut::Rect& rRect, const GXColor& rColor);
        void setupGX(const GXSettingFor2D&);
    }

}; // ezrender

}; //nrel

#endif
