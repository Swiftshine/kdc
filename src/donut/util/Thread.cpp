#pragma peephole once
#include <donut/util/Thread.hpp>

using util::Thread;

s32 Thread::GetCurrentThreadPriority() {
    OSThread* curThread = OSGetCurrentThread();
    return OSGetThreadPriority(curThread);
}

Thread::Thread(mem::IAllocator& rAllocator, u32 size, s32 arg3, OSThreadFunc threadFunc, void* arg5)
    : mDataBlock(size, 0x20, rAllocator)
{
    s32 blockData  = (s32)mDataBlock.block().mStartAddress;
    //Adding blockData and size makes sense in this context because then we can get an address for the area of data we want
    OSCreateThread(&mThread, threadFunc, arg5, (void*)(blockData + size), size, arg3, 0);
    OSResumeThread(&mThread);
}

//https://decomp.me/scratch/89lau
Thread::~Thread() {
    OSCancelThread(&mThread);
}
