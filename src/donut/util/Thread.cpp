#pragma peephole once
#include <donut/util/Thread.hpp>

using util::Thread;

s32 Thread::GetCurrentThreadPriority() {
    OSThread* curThread = OSGetCurrentThread();
    return OSGetThreadPriority(curThread);
}

Thread::Thread(mem::IAllocator& rAllocator, u32 stackSize, s32 prio, OSThreadFunc threadFunc, void* pFuncArg)
    : mStack(stackSize, 32, rAllocator)
{
    s32 stackStart  = (s32)mStack.block().mStartAddress;
    OSCreateThread(&mThread, threadFunc, pFuncArg, (void*)(stackStart + stackSize), stackSize, prio, 0);
    OSResumeThread(&mThread);
}

//https://decomp.me/scratch/89lau
Thread::~Thread() {
    OSCancelThread(&mThread);
}
