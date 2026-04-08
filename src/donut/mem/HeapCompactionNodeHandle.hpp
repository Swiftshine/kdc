#ifndef DONUT_MEM_HEAP_COMPACTION_NODE_HANDLE_HPP
#define DONUT_MEM_HEAP_COMPACTION_NODE_HANDLE_HPP

#include <donut/mem/MemBlock.hpp>

namespace mem {
class HeapCompactionNode;

class HeapCompactionNodeHandle {
public:
    //NOTE: Merged into nw4r::g3d::LightObj::LightObj()
    HeapCompactionNodeHandle();
    //NOTE: Merged into nw4r::g3d::Camera::Camera(nw4r::g3d::CameraData*)
    HeapCompactionNodeHandle(HeapCompactionNode& rNode);

    //TODO: Does this exist?
    ~HeapCompactionNodeHandle();

    //NOTE: Merged into nrel::mem::ExpHeapBlockIterator::hasNext() const
    bool isValid() const;

    //NOTE: Merged into GKI_getfirst
    HeapCompactionNode* node() const;

    MemBlock block() const;

    /* 0x0 */ HeapCompactionNode* mNode;
};
}

#endif
