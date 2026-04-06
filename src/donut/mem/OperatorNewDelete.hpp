#ifndef DONUT_MEM_OPERATORNEWDELETE_HPP
#define DONUT_MEM_OPERATORNEWDELETE_HPP

#include <types.h>

namespace mem {

class IAllocator;

namespace OperatorNewDelete {
    void SetDefaultAllocator(IAllocator& rAllocator);
    void SetGlobalNewDeleteAllocator(IAllocator& rAllocator);
    void UnsetGlobalNewDeleteAllocator(IAllocator& rAllocator);
} //namespace OperatorNewDelete

} //namespace mem

void* operator new(u32 size);
//Note: merged into operator new(u32)
void* operator new[](u32 size);
void* operator new(u32 size, mem::IAllocator& rAllocator);

void operator delete(void* pData);
//NOTE: merged into operator delete(void*)
void operator delete[](void* pData);

#endif
