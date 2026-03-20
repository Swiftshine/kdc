#ifndef HEL_COMMON_MUTABLEARRAY_HPP
#define HEL_COMMON_MUTABLEARRAY_HPP

#include <types.h>

namespace hel { namespace common {

template <typename T, size_t S>
class MutableArray {
public:
    ~MutableArray();
private:
    /* 0x0 */ T mArray[S];
};
}}
#endif
