#include <revolution/BASE.h>
#include <revolution/DB.h>
#include <revolution/OS.h>

OSDebugInterface* __DBInterface;

BOOL DBIsDebuggerPresent() {
    if (__DBInterface == NULL) {
        return FALSE;
    }
    return __DBInterface->usingDebugger;
}
