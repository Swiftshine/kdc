#ifndef DONUT_APP_ROMFONTWRAPPER_HPP
#define DONUT_APP_ROMFONTWRAPPER_HPP

#include <types.h>
#include <nw4r/ut.h>

namespace app {
    class RomFontWrapper {
    public:
        RomFontWrapper();
        ~RomFontWrapper();

        nw4r::ut::RomFont& font();
    private:
        STRUCT_FILL(0x28);
    };
}

#endif
