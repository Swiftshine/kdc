#ifndef DONUT_MEM_IALLOCATOR_HPP
#define DONUT_MEM_IALLOCATOR_HPP

#include <types.h>
namespace mem {

class IAllocator {
    public:

    //NOTE: Gets merged into IScene's deconstructor
    /* 0x08 */ virtual ~IAllocator() = 0;
    /* 0x0C */ virtual void* allocatorAlloc(u32 size, s32 arg2) = 0;
    /* 0x10 */ virtual void allocatorFree(void* pData) = 0;

};

}

#endif
