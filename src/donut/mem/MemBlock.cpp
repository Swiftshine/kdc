#pragma peephole off
#include <donut/mem/MemBlock.hpp>

using mem::MemBlock;

MemBlock MemBlock::EmptyBlock() {
    return MemBlock(nullptr, 0);
}

MemBlock::MemBlock(void* pData, u32 size)
    : mSize(size)
    , mStartAddress(pData)
{ }
