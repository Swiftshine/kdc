#ifndef DONUT_MEM_DATA_BLOCK_HPP
#define DONUT_MEM_DATA_BLOCK_HPP

#include <mem/MemBlock.hpp>
#include <types.h>

namespace mem {
class MemBlock;
class IAllocator;

class DataBlock {
public:
    DataBlock(u32 size, s32 arg2, IAllocator& rAllocator);
    ~DataBlock();

    MemBlock block() const {
        return mBlock;
    }

    /* 0x0 */ IAllocator* mAllocator;
    /* 0x4 */ MemBlock mBlock;
};
}

#endif
