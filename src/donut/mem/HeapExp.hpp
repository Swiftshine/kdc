#ifndef DONUT_MEM_HEAPEXP_HPP
#define DONUT_MEM_HEAPEXP_HPP

#include <donut/mem/IAllocator.hpp>

namespace mem {

class HeapExp : public IAllocator {

public:

    /* 0x08 */ virtual ~HeapExp();
    /* 0x0C */ virtual void* allocatorAlloc(u32, s32);
    /* 0x10 */ virtual void allocatorFree(void* pData);

    void* alloc(u32 size);
    void free(void* pData);
    IAllocator& allocFromTailAllocator();
};

}

#endif
