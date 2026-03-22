#ifndef DONUT_MEM_HEAPEXP_HPP
#define DONUT_MEM_HEAPEXP_HPP

#include "mem/IAllocator.hpp"

namespace mem {

class HeapExp {

public:
    IAllocator& allocFromTailAllocator();
};

}

#endif
