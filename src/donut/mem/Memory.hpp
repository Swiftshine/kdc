#ifndef DONUT_MEM_MEMORY_HPP
#define DONUT_MEM_MEMORY_HPP

#include <hel/common/ExplicitSingleton.hpp>

#include "mem/HeapCompaction.hpp"
#include "mem/HeapExp.hpp"

namespace mem {

class IAllocator;

class Memory {
public:
    DECL_EXPLICIT_SINGLETON(Memory);

    HeapExp& mem1FixHeap();
    HeapExp& mem2FixHeap();
    HeapExp& sceneHeap();
    HeapCompaction& /* probably? */ externalHeap();

    static void SetupIfNotSetup();
};

}

#endif
