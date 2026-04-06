#pragma peephole off
#include <donut/mem/HeapCompactionNode.hpp>

using mem::HeapCompactionNode;

mem::MemBlock HeapCompactionNode::block() const {
    return mem::MemBlock(mStartAddress, size());
}

u32 HeapCompactionNode::size() const {
    return mSize & 0x7FFFFFFF;
}

void HeapCompactionNode::setSize(u32 size) {
    mSize &= 0x80000000;
    u32 sizeBitOperated = size & 0x7FFFFFFF;
    u32 sizeVal = mSize | sizeBitOperated;
    mSize = sizeVal;
}

void HeapCompactionNode::setAddrAndSize(void* pAddress, u32 size) {
    mStartAddress = pAddress;
    setSize(size);
}

bool HeapCompactionNode::isFree() const {
    return (mSize & 0x80000000) != 0;
}

//https://decomp.me/scratch/KT6Ic
void HeapCompactionNode::setIsFree(bool isFree) {
    mSize &= 0x7FFFFFFF;
    u32 secondVal = 0x80000000;
    secondVal &= isFree;
    mSize |= secondVal;
}
