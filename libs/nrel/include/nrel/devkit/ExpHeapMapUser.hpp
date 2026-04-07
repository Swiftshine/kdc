#ifndef NREL_EXP_HEAP_MAP_USER_HPP
#define NREL_EXP_HEAP_MAP_USER_HPP

#include <nrel/devkit/IHeapMapUser.hpp>
#include <nrel/mem/ExpHeapAccessor.hpp>

namespace nrel { namespace devkit { namespace heapmap {
    class ExpHeapMapUser : public IHeapMapUser  {
    public:
        ExpHeapMapUser(MEMiHeapHead* pHeapHead,  const char* pArg2);
        /* 0x8 */ virtual ~ExpHeapMapUser();

        /* 0x4 */ mem::ExpHeapAccessor mAccessor;
        /* 0x8 */ const char* m_8;
    };


}; //heapmap

}; // devkit

}; //nrel

#endif
