#pragma peephole off
#include <hel/common/PointerWrapper.hpp>
#include <donut/mem/OperatorNewDelete.hpp>
#include <donut/mem/Memory.hpp>

namespace {
    static hel::common::PointerWrapper<mem::IAllocator> t_allocator;
    static hel::common::PointerWrapper<mem::IAllocator> t_globalNewDeleteAllocator;

    mem::IAllocator* t_allocatorRef() {
        mem::Memory::SetupIfNotSetup();
        if (t_globalNewDeleteAllocator != nullptr) {
            return t_globalNewDeleteAllocator.getPtr();
        } else if (t_allocator != nullptr) {
            return t_allocator.getPtr();
        }
        return &mem::Memory::Instance->mem1FixHeap();
    }

    void* t_operatorNew(u32 size) DECOMP_DONT_INLINE {
        return t_allocatorRef()->allocatorAlloc(size, 4);
    }

    void* t_operatorNew(u32 size, mem::IAllocator& rAllocator) DECOMP_DONT_INLINE {
        return rAllocator.allocatorAlloc(size, 4);
    }

    void t_operatorDelete(void* pData) DECOMP_DONT_INLINE {
        if (pData != nullptr) {
            t_allocatorRef()->allocatorFree(pData);
        }
    }
}

void* operator new(u32 size, mem::IAllocator& rAllocator) {
    return t_operatorNew(size, rAllocator);
}

void* operator new(u32 size) {
    return t_operatorNew(size);
}

void operator delete(void* pData) {
    t_operatorDelete(pData);
}

namespace mem {
    namespace OperatorNewDelete {
        void SetDefaultAllocator(IAllocator &rAllocator) {
            t_allocator = &rAllocator;
        }

        void SetGlobalNewDeleteAllocator(IAllocator &rAllocator) {
            t_globalNewDeleteAllocator = &rAllocator;
        }

        void UnsetGlobalNewDeleteAllocator(IAllocator &rAllocator) {
            t_globalNewDeleteAllocator = nullptr;
        }
    }
}

//NOTE: All functions below are code merged into others. Refer to the header for more details

void* operator new[](u32 size) {
    return t_operatorNew(size);
}

void operator delete[](void* pData) {
    t_operatorDelete(pData);
}
