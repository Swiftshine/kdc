#ifndef DONUT_GFX_IDRAWER_HPP
#define DONUT_GFX_IDRAWER_HPP

namespace gfx {

class IDrawer {
public:
    /* 0x8 */ virtual ~IDrawer();
    /* 0xC */ virtual void drawerExecDraw() = 0;
};

}

#endif
