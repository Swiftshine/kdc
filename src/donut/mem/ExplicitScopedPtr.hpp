#ifndef DONUT_MEM_EXPLICITSCOPEDPTR_H
#define DONUT_MEM_EXPLICITSCOPEDPTR_H

#include <types.h>

namespace mem {

template <typename T>
class ExplicitScopedPtr {
public:
    ExplicitScopedPtr(T* pPtr)
        : mPtr(pPtr)
    { }

    /// Destructs the pointer.
    void destruct();
    /// Returns if the pointer is not `nullptr`.
    bool isConstruct() const;

    T* operator->();
private:
    /* 0x4 */ T* mPtr;
};

namespace ExplicitScopedPtrUtil {
    void CheckPointerIsValid(const void*) { } // weak
}

} // mem

#endif
