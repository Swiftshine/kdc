#pragma peephole off
#include <donut/mem/HeapExp.hpp>
#include <donut/mem/Utility.hpp>
#include <donut/mem/HeapMapUserRepos.hpp>

namespace mem {

    //https://decomp.me/scratch/p0RYK
    HeapExp::HeapExp(const hel::common::FixedString<32>& rHeapName, const MemBlock& rMemBlock, bool arg3, bool arg4)
        : mHeapName(rHeapName)
        , mMemBlock(rMemBlock)
        , mUsingBlockCount(0)
        , m_30(arg4)
        , m_34(MEMCreateExpHeapEx(rMemBlock.mStartAddress, rMemBlock.mSize, 0))
        , m_38()
        , m_48()
        , mTailAllocator(*this)
        , mMapUser(m_34, nullptr)
    {

    }

    //NOTE: Technically matches but will need multiple things to be defined for code merging
    HeapExp::AllocFromTailAllocator::~AllocFromTailAllocator() { }

    //https://decomp.me/scratch/sjM2w
    HeapExp::~HeapExp() {
        HeapMapUserRepos::Unregister(*(nrel::devikit::heapmap::IHeapMapUser*)&m_38);
        m_38.destruct();
        m_48.destruct();
        MEMDestroyExpHeap(m_34);
    }

    void* HeapExp::alloc(u32 size) {
        return alloc(size, 4);
    }

    void* HeapExp::alloc(u32 size, s32 alignment) {
        return alloc(size, alignment, false);
    }

    void* HeapExp::alloc(u32 size, s32 alignment, bool isNegativeAligned) {

        //TODO: alignmentFactor could be a tenary
        MEMiHeapHead* temp = m_34;
        s32 alignmentFactor;

        if (isNegativeAligned) {
            alignmentFactor = -1;
        } else {
            alignmentFactor = 1;
        }

        void* data = MEMAllocFromExpHeapEx(temp, size, alignment * alignmentFactor);

        if (!m_30) {
            Utility::MemSetU32(MemBlock(data, size),  0x7fbfffff);
        }
        mUsingBlockCount++;

        return data;
    }

    void HeapExp::free(void* pData) {
        mUsingBlockCount--;
        MEMFreeToExpHeap(m_34, pData);
    }

    //https://decomp.me/scratch/QTBYr
    void* HeapExp::allocatorAlloc(u32 size, s32 alignment) {
        return alloc(size, alignment);
    }

    //https://decomp.me/scratch/tgbZI
    void HeapExp::allocatorFree(void* pData) {
        free(pData);
    }

     //NOTE: Technically matches but will need multiple things to be defined for code merging
    const char* HeapExp::heapName() const {
        return mHeapName.str();
    }

    MemBlock HeapExp::heapMemBlock() const {
        return mMemBlock;
    }

     //NOTE: Technically matches but will need multiple things to be defined for code merging
    s32 HeapExp::heapUsingBlockCount() const {
        return mUsingBlockCount;
    }

    void HeapExp::heapDump() const {
        nrel::mem::ExpHeapAccessor accessor(m_34);
        accessor.dump(nrel::mem::ExpHeapAccessor::DUMP_STYLE_0);
    }

    HeapExp::AllocFromTailAllocator::AllocFromTailAllocator(HeapExp& rHeap)
        : mHeap(rHeap)
    { }

    void* HeapExp::AllocFromTailAllocator::allocatorAlloc(u32 size, s32 alignment) {
        return mHeap.alloc(size, alignment, true);
    }

    //https://decomp.me/scratch/gUdsl
    void HeapExp::AllocFromTailAllocator::allocatorFree(void* pData) {
        mHeap.free(pData);
    }
};
