#ifndef RVL_SDK_DB_H
#define RVL_SDK_DB_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

//unused
void DBInit(void);
//unused
void __DBExceptionDestinationAux(void);
//unused
void __DBExceptionDestination(void);
//unused
BOOL __DBIsExceptionMarked(u8 exc);
//unused
void DBPrintf(const char* msg, ...);

BOOL DBIsDebuggerPresent();
#ifdef __cplusplus
}
#endif
#endif
