#ifndef DONUT_MEM_MEMORY_BLOCK_HPP
#define DONUT_MEM_MEMORY_BLOCK_HPP

#include <types.h>

namespace mem {

class MemBlock {
public:
    MemBlock(void* pData, u32 size);

    static MemBlock EmptyBlock();

    //NOTE: Is merged into GetZeroBufferAddress__Q44nw4r3snd6detail9AxManagerFv
    void* startAddress() const;

    /* 0x0 */ u32 mSize;
    /* 0x4 */ void* mStartAddress;
};
}

#endif
