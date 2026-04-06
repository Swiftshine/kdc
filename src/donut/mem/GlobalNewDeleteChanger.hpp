#ifndef DONUT_MEM_GLOBAL_NEW_DELETE_CHANGER_HPP
#define DONUT_MEM_GLOBAL_NEW_DELETE_CHANGER_HPP

#include <types.h>

namespace mem {
    class IAllocator;

    class GlobalNewDeleteChanger {
    public:
        GlobalNewDeleteChanger(IAllocator& rAllocator);
        ~GlobalNewDeleteChanger();
    private:
        /* 0x0 */ IAllocator& mAllocator;
    };
}

#endif
