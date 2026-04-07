#ifndef HEL_FIXED_STRING_HPP
#define HEL_FIXED_STRING_HPP

#include <hel/common/Traits.hpp>

namespace hel {
namespace common {

template <size_t S>
class FixedString {
public:
    FixedString(const char* pString)
        : mString(0)
    {
        Traits<char>::Strncpy(mString, pString, S);
    }

    inline char* str() const {
        return (char*)mString;
    }

private:
    /* 0x0 */ char mString[S];
};

} // common
} // hel

#endif
