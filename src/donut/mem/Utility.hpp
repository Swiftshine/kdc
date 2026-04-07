#ifndef DONUT_MEM_UTILITY_HPP
#define DONUT_MEM_UTILITY_HPP

#include <types.h>

namespace mem {
    class MemBlock;

    namespace Utility {
        void* MemSetU32(const MemBlock& rMemBlock, u32 arg2);
    };
}

#endif
