#ifndef DONUT_FILE_UTILITY_HPP
#define DONUT_FILE_UTILITY_HPP

#include <donut/mem/MemBlock.hpp>

namespace mem {
    class IAllocator;
}

namespace file {

    namespace Utility {
        bool IsExistFileOnUsbOrDvd(const char* pFilePath);
        //NOTE: Merged into __wpadNoAlloc
        u32 LatestUpdateDateOnUSB(const char*, bool);

        void IsFileLoadWarningEnable();

        mem::MemBlock UncompressedFile(const mem::MemBlock&, mem::IAllocator&);
        mem::MemBlock LoadFromUsbOrDvd(const char*, mem::IAllocator&);
    };
}

#endif
