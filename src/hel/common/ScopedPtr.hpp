#ifndef HEL_COMMON_SCOPEDPTR_HPP
#define HEL_COMMON_SCOPEDPTR_HPP

#include <types.h>

namespace hel { namespace common {

template<typename T>
class ScopedPtr {
public:
    ~ScopedPtr() {
        if (ptr != nullptr) {
            delete ptr;
        }
    }
    void reset(T* ptr);

    T* operator->();

    operator T*() {
        return ptr;
    }
private:
    T* ptr;
};

} // common
} // hel
#endif
