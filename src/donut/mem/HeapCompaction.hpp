#ifndef DONUT_MEM_HEAPCOMPACTION_HPP
#define DONUT_MEM_HEAPCOMPACTION_HPP

#include <donut/mem/IAllocator.hpp>
#include <donut/mem/HeapCompactionNodeHandle.hpp>

namespace mem {

class HeapCompaction {
public:
    void compaction();
    HeapCompactionNodeHandle search(void* pData);

    /* 0x0 */ s32 m_0;
    /* 0x4 */ IAllocator m_4;

};

}

#endif
