#pragma peephole off
#include <donut/mem/AllocatorHandle.hpp>
#include <donut/mem/IAllocator.hpp>

//NOTE: This whole TU is quite literally only comprised of code merged functions.
//Refer to the header for more details.

namespace mem {
    AllocatorHandle::AllocatorHandle()
        : mAllocator(0)
    { }

    AllocatorHandle::AllocatorHandle(IAllocator& rAllocator)
        : mAllocator(&rAllocator)
    { }

    bool AllocatorHandle::isValid() const {
        return mAllocator != nullptr;
    }

    IAllocator* AllocatorHandle::obj() const {
        return mAllocator;
    }
};
