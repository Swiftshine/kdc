#ifndef HEL_FIXED_STRING_IN_HPP
#define HEL_FIXED_STRING_IN_HPP

#include <types.h>

namespace hel {
namespace common {

template <typename T, size_t S>
class FixedStringIN {
public:
    FixedStringIN();

    static FixedStringIN<T, S> FromFormat(const T* pStr, ...);

    inline T* str() const {
        return (T*)mString;
    }

private:
    /* 0x0 */ T mString[S];
};

} // common
} // hel

#endif
