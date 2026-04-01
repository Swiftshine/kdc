#ifndef HEL_COMMON_EXPLICITSINGLETON_HPP
#define HEL_COMMON_EXPLICITSINGLETON_HPP

#include <types.h>

namespace hel { namespace common {

template<typename T>
class ExplicitSingleton {
public:
    ~ExplicitSingleton();

    static bool IsExist() {
        return object_ != nullptr;
    }

    inline T* operator->() {
        return object_;
    }

    inline const T* operator->() const {
        return object_;
    }

    inline void operator=(T* pOther) {
        object_ = pOther;
    }

    inline bool operator!=(T* pOther) {
        return object_ != pOther;
    }

    inline T* object() {
        return object_;
    }
private:
    static T* object_;
};

} // common
} // hel

#define DECL_EXPLICIT_SINGLETON(T) static hel::common::ExplicitSingleton<T> Instance;

#endif
