#ifndef DONUT_GFX_UTLITY_HPP
#define DONUT_GFX_UTLITY_HPP

#include <types.h>

namespace gfx {
namespace Utility {
    void SetGXStateDirty();
    void SetupGXForScreen2D(f32, f32);
    u32 CurrentGameWidth();
    u32 CurrentGameHeight();
}
}

#endif
