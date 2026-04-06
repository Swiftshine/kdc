#ifndef DONUT_MEM_HEAP_COMPACTION_NODE_HPP
#define DONUT_MEM_HEAP_COMPACTION_NODE_HPP

#include <donut/mem/MemBlock.hpp>

namespace mem {

    class HeapCompactionNode {
    public:

        MemBlock block() const;
        u32 size() const;
        bool isFree() const;

        void setSize(u32 size);
        void setAddrAndSize(void* pAddress, u32 size);
        void setIsFree(bool isFree);

        /* 0x0 */ void* mStartAddress;
        /* 0x4 */ u32 mSize;
    };
}

#endif
