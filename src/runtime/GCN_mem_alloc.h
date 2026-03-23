#ifndef RUNTIME_GCN_MEM_ALLOC_H
#define RUNTIME_GCN_MEM_ALLOC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void __sys_free(void* block);

#define OSRoundUp32B(x) (((unsigned int)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((unsigned int)(x)) & ~(32 - 1))

#ifdef __cplusplus
}
#endif
#endif
