#ifndef DONUT_SCN_STEP_COMMON_PARAM_H
#define DONUT_SCN_STEP_COMMON_PARAM_H

// clang-format off
#include <macros.h>
#include <types.h>
namespace scn { namespace step { namespace common {
    struct Param 
    { 
        STRUCT_FILL(0x4F8);
        u32 mUnk4F8;
    };
} // common
} // step
} // scn
// clang-format on

#endif
