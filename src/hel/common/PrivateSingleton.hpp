#ifndef HEL_COMMON_PRIVATE_SINGLETON_HPP
#define HEL_COMMON_PRIVATE_SINGLETON_HPP

#include <donut/scn/IScene.hpp>
#include <types.h>

namespace hel { namespace common {

//TODO: This  inherits something that has its deconstructor merged into IScene
template <typename T>
class PrivateSingleton {
public:
    inline PrivateSingleton() {
        isExist_ = true;
    }
    ~PrivateSingleton() {
        isExist_ = false;
    }

private:
    static bool isExist_;
};

} // common
} // hel

#endif
