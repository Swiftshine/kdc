#ifndef DONUT_UTIL_DISABLE_INTERRUPTS_HPP
#define DONUT_UTIL_DISABLE_INTERRUPTS_HPP

#include <revolution/OS.h>

namespace util {

class DisableInterrupts {
public:

    //TODO: What is this type bro
    DisableInterrupts()
        : mStatus(OSDisableInterrupts())
    { }

    ~DisableInterrupts() DONT_INLINE {
        OSRestoreInterrupts(mStatus);
    }

private:
    /* 0x0 */ u8 mStatus;
};
}

#endif
