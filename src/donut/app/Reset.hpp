#ifndef DONUT_APP_RESET_HPP
#define DONUT_APP_RESET_HPP

#include <types.h>

namespace app {
    class Reset {
    public:
        Reset();
        ~Reset();
    private:
        STRUCT_FILL(0x54);
    };
}

#endif
