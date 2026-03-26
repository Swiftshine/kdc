#ifndef RVL_SDK_VERSION_H
#define RVL_SDK_VERSION_H
#include <types.h>

#define RVL_LIB_VERSION(NAME, ORIGINAL_DATE, ORIGINAL_TIME, ORIGINAL_CWCC)     \
    const char* __##NAME##Version =                                            \
        "<< RVL_SDK - " #NAME " \trelease build: " ORIGINAL_DATE               \
        " " ORIGINAL_TIME " (" ORIGINAL_CWCC ") >>"

#define RVL_LIB_VERSION_KDC(NAME, TIME) RVL_LIB_VERSION(NAME, "Aug 23 2010", TIME, "0x4302_145")
#endif
