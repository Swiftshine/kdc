#pragma peephole off
#include <donut/gfx/GXFifoMemoryManager.hpp>
#include <donut/mem/Memory.hpp>

using gfx::GXFifoMemoryManager;

GXFifoMemoryManager::GXFifoMemoryManager(u32 size, u32 arg2)
    : hel::common::PrivateSingleton<GXFifoMemoryManager>()
    , mSize(size)
    , m_4(arg2)
    , mData(mem::Memory::Instance->mem1FixHeap().allocatorAlloc(mSize + 0x400 , 0x20))
    , mWriteEnabled(true)
    , mMutex()
{
    DCInvalidateRange(data(), mSize);
}

GXFifoMemoryManager::~GXFifoMemoryManager() {
    mem::Memory::Instance->mem1FixHeap().free(mData);
    mData = nullptr;
}

void* GXFifoMemoryManager::data() {
    return (void*)((s32)mData + 0x3FF & 0xFFFFFC00);
}

void GXFifoMemoryManager::setWriteEnable() {
    mWriteEnabled = true;
}

void GXFifoMemoryManager::setWriteDisable() {
    mWriteEnabled = false;
}

u32 GXFifoMemoryManager::size() const {
    return mSize;
}

util::Mutex* GXFifoMemoryManager::mutex() {
    return &mMutex;
}
