#ifndef DONUT_MEM_HEAPEXP_HPP
#define DONUT_MEM_HEAPEXP_HPP

#include "mem/IAllocator.hpp"

namespace mem {

class HeapExp {

public:

    /* 0x0 */ virtual ~HeapExp();
    /* 0x4 */ virtual void* allocatorAlloc(u32, s32);

    void free(void* pData);
    IAllocator& allocFromTailAllocator();
};

}

#endif
