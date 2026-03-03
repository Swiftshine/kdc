#ifndef HEL_COMMON_EXPLICITSINGLETON_HPP
#define HEL_COMMON_EXPLICITSINGLETON_HPP

#include <types.h>

namespace hel { namespace common {

template<typename T>
class ExplicitSingleton {
public:
    ~ExplicitSingleton() { }

    static bool IsExist() {
        return object_ != nullptr;
    }

    inline T* operator->() {
        return object_;
    }

    inline const T* operator->() const {
        return object_;
    }
private:
    static T* object_;
};

} // common
} // hel

#endif
