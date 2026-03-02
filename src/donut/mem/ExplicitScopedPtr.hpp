#ifndef DONUT_MEM_EXPLICITSCOPEDPTR_H
#define DONUT_MEM_EXPLICITSCOPEDPTR_H

namespace mem {

template <typename T>
class ExplicitScopedPtr {
public:
    ExplicitScopedPtr(T* pPtr)
        : mPtr(pPtr)
    { }

    /* 0x08 */ virtual ~ExplicitScopedPtr();
    /* 0x0C */ virtual void vfC();
    /* 0x10 */ virtual void vf10();

    /// Destructs the pointer.
    void destruct();
    /// Returns if the pointer is not `nullptr`.
    bool isConstruct() const;

    T* operator->();
private:
    /* 0x4 */ T* mPtr;
};

} // mem

#endif
