#ifndef NREL_MEM_EXP_HEAP_ACCESSOR_HPP
#define NREL_MEM_EXP_HEAP_ACCESSOR_HPP

#include <revolution/MEM.h>

namespace nrel { namespace mem {
    class ExpHeapAccessor {
    public:
        enum DumpStyle {
            DUMP_STYLE_0,
        };

        ExpHeapAccessor(MEMiHeapHead* pHeapHead);
        ~ExpHeapAccessor();
        void dump(DumpStyle dumpStyle) const;

    private:
        /* 0x0 */ MEMiHeapHead* mHeapHead;
    };

}; // mem

}; //nrel

#endif
