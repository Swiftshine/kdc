#ifndef DONUT_FILE_FDGMANAGER_HPP
#define DONUT_FILE_FDGMANAGER_HPP

#include <types.h>

#include "mem/IAllocator.hpp"

namespace file {

class FDGManager {
public:
    FDGManager(mem::IAllocator& rAllocator);
    ~FDGManager();
private:
    STRUCT_FILL(0x70);
};

}

#endif
