#pragma peephole off
#include <donut/mem/HeapCompactionNodeHandle.hpp>
#include <donut/mem/HeapCompactionNode.hpp>

namespace mem {

    MemBlock HeapCompactionNodeHandle::block() const {
        return mNode->block();
    }
    //NOTE: All functions below are code merged into others. Refer to the header for more details
    HeapCompactionNodeHandle::HeapCompactionNodeHandle()
        : mNode(0)
    { }

    HeapCompactionNodeHandle::HeapCompactionNodeHandle(HeapCompactionNode& rNode)
        : mNode(&rNode)
    { }

    bool HeapCompactionNodeHandle::isValid() const {
        return mNode != nullptr;
    }

    HeapCompactionNode* HeapCompactionNodeHandle::node() const {
        return mNode;
    }
};
