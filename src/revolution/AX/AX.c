#include <revolution/AX.h>
#include <revolution/OS.h>
#include <revolution/version.h>

RVL_LIB_VERSION_KDC(AX, "17:29:51");

static BOOL __init = FALSE;

void AXInit(void) {
    AXInitEx(0);
}

BOOL AXIsInit() {
    return __init;
}

void AXInitEx(u32 mode) {
    if (!__init) {
        OSRegisterVersion(__AXVersion);

        __AXAllocInit();
        __AXVPBInit();
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(mode);

        __init = TRUE;
    }

}
