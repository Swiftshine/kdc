#ifndef DONUT_MEM_IALLOCATOR_HPP
#define DONUT_MEM_IALLOCATOR_HPP

#include <types.h>
namespace mem {

class IAllocator {
    public:

    //NOTE: Gets merged into IScene's deconstructor
    ~IAllocator();

    //TODO: Actually figure out and define these
    //Please note none of these are symbols in the map file and seem to be inlined
    virtual void unknown1();
    virtual void* getPtr();
    virtual void freeData(void* pData);

};

}

#endif
