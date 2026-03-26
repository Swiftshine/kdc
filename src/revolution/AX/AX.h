#ifndef RVL_SDK_AX_H
#define RVL_SDK_AX_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void AXInit(void);
BOOL AXIsInit();

//unused besides inline
void AXInitEx(u32 mode);

#ifdef __cplusplus
}
#endif
#endif
