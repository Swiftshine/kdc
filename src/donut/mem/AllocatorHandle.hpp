#ifndef DONUT_MEM_ALLOCATOR_HANDLE_HPP
#define DONUT_MEM_ALLOCATOR_HANDLE_HPP

#include <types.h>

namespace mem {
class IAllocator;

class AllocatorHandle {
public:
    //NOTE: Merged into nw4r::g3d::LightObj::LightObj()
    AllocatorHandle();
    //NOTE: Merged into nw4r::g3d::Camera::Camera(nw4r::g3d::CameraData*)
    AllocatorHandle(IAllocator& rAllocator);

    //TODO: Does this exist?
    ~AllocatorHandle();

    //NOTE: Merged into nrel::mem::ExpHeapBlockIterator::hasNext() const
    bool isValid() const;

    //NOTE: Merged into GKI_getfirst
    IAllocator* obj() const;

    /* 0x0 */ IAllocator* mAllocator;
};
}

#endif
