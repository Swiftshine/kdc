#pragma peephole off
#include <donut/mem/DataBlock.hpp>
#include <donut/mem/IAllocator.hpp>

using mem::DataBlock;

DataBlock::DataBlock(u32 size, s32 unused, IAllocator& rAllocator)
    : mAllocator(&rAllocator)
    , mBlock(rAllocator.getPtr(), size)
{}

DataBlock::~DataBlock() {
    mAllocator->freeData(mBlock.mStartAddress);
}
