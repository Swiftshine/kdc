#ifndef DONUT_UTIL_THREAD_HPP
#define DONUT_UTIL_THREAD_HPP

#include <revolution/OS.h>
#include <donut/mem/DataBlock.hpp>

namespace util {
    class Thread {
        Thread(mem::IAllocator&, u32, s32, OSThreadFunc, void*);
        ~Thread();

        s32 GetCurrentThreadPriority();

        /* 0x00 */ mem::DataBlock mDataBlock;
        /* 0x08 */ s32 m_8;
        /* 0x10 */ OSThread mThread;
    };
}

#endif
