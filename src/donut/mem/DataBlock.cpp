#pragma peephole off
#include <donut/mem/DataBlock.hpp>
#include <donut/mem/IAllocator.hpp>

using mem::DataBlock;

DataBlock::DataBlock(u32 size, s32 arg2, IAllocator& rAllocator)
    : mAllocator(&rAllocator)
    , mBlock(rAllocator.allocatorAlloc(size, arg2), size)
{}

DataBlock::~DataBlock() {
    mAllocator->allocatorFree(mBlock.mStartAddress);
}
