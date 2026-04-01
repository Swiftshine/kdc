#ifndef DONUT_GFX_XFBMANAGER_HPP
#define DONUT_GFX_XFBMANAGER_HPP

#include <donut/gfx/VISetting.hpp>
#include <donut/mem/DataBlock.hpp>

namespace gfx {

class XFBManager {
public:

    XFBManager(const gfx::VISetting&);

    void* drawTargetXFB();
    void changeDrawTargetXFB();

    void* target1();
    void* target2();

    /* 0x00 */ mem::DataBlock mTarget1;
    /* 0x0C */ mem::DataBlock mTarget2;
    /* 0x18 */ bool mIsDrawTarget1;

};

}

#endif
