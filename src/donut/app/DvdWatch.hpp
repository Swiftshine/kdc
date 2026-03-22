#ifndef DONUT_APP_DVDWATCH_HPP
#define DONUT_APP_DVDWATCH_HPP

#include <types.h>
#include <nw4r/ut.h>
#include "gfx/GameScreen.hpp"

namespace app {

class System;

class DvdWatch {
public:
    DvdWatch(System& rSystem, nw4r::ut::RomFont& rFont, gfx::GameScreen& rGameScreen);
    ~DvdWatch();
private:
    STRUCT_FILL(0x344);
};

}

#endif
