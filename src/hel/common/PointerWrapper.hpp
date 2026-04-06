#ifndef HEL_POINTER_WRAPPER_HPP
#define HEL_POINTER_WRAPPER_HPP

#include <types.h>

namespace hel {
namespace common {

template <typename T>
class PointerWrapper {
public:
    //NOTE: Merged into nw4r::g3d::LightObj::LightObj()
    PointerWrapper() {
        mPointer = nullptr;
    }

    inline void operator=(const T* pOther) {
        mPointer = (T*)pOther;
    }

    inline bool operator!=(const T* pOther) {
        return mPointer != pOther;
    }

    inline T* getPtr() {
        return mPointer;
    }

private:
    /* 0x0 */ T* mPointer;
};

} // common
} // hel

#endif
