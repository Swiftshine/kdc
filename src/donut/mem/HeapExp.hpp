#ifndef DONUT_MEM_HEAPEXP_HPP
#define DONUT_MEM_HEAPEXP_HPP

#include <donut/mem/IAllocator.hpp>
#include <donut/mem/MemBlock.hpp>
#include <donut/util/PlacementNew.hpp>
#include <nrel/devkit/ExpHeapMapUser.hpp>
#include <hel/common/FixedString.hpp>

namespace mem {

class HeapExp : public IAllocator {
public:
    class AllocFromTailAllocator : public IAllocator {
        public:

        AllocFromTailAllocator(HeapExp& rHeap);

        //NOTE: Function is replaced by a branch to Delegate<Fv_b,64>::~Delegate<Fv_b,64>()
        /* 0x08 */ virtual ~AllocFromTailAllocator();
        /* 0x0C */ virtual void* allocatorAlloc(u32, s32);
        /* 0x10 */ virtual void allocatorFree(void* pData);

        /* 0x4 */ HeapExp& mHeap;
    };

    HeapExp(const hel::common::FixedString<32>& rHeapName, const MemBlock& rMemBlock, bool arg3, bool arg4);

    /* 0x08 */ virtual ~HeapExp();
    /* 0x0C */ virtual void* allocatorAlloc(u32, s32);
    /* 0x10 */ virtual void allocatorFree(void* pData);
    //NOTE: Function is replaced by a branch to Delegate<Fv_v,64>::allocatorAlloc()
    /* 0x14 */ virtual const char* heapName() const;
    /* 0x18 */ virtual MemBlock heapMemBlock() const;
    //NOTE: Function is replaced by a branch to homebutton::gui::PaneComponent::getPane() due to code merging
    /* 0x1C */ virtual s32 heapUsingBlockCount() const;
    /* 0x20 */ virtual void heapDump() const;

    void* alloc(u32 size);
    void* alloc(u32 size, s32 alignment);
    void* alloc(u32 size, s32 alignment, bool isNegativeAligned);
    void free(void* pData);

    IAllocator& allocFromTailAllocator();

    /* 0x04 */ hel::common::FixedString<32> mHeapName;
    /* 0x24 */ MemBlock mMemBlock;
    /* 0x2C */ s32 mUsingBlockCount;
    /* 0x30 */ bool m_30;
    /* 0x34 */ MEMiHeapHead* m_34;
    /* 0x38 */ util::PlacementNew<nrel::devkit::heapmap::ExpHeapMapUser> m_38; //TODO: This is most likely a different PlacementNew merged into HeapExp's
    /* 0x3C */ nrel::devkit::heapmap::ExpHeapMapUser mMapUser;
    /* 0x48 */ util::PlacementNew<AllocFromTailAllocator> m_48;
    /* 0x4C */ AllocFromTailAllocator mTailAllocator;

};

}

#endif
