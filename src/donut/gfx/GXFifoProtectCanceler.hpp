#ifndef DONUT_GFX_GXFIFOPROTECTCANCELER_HPP
#define DONUT_GFX_GXFIFOPROTECTCANCELER_HPP

namespace gfx {

class GXFifoMemoryManager;

class GXFifoProtectCanceler {
public:
    GXFifoProtectCanceler(GXFifoMemoryManager&);
    ~GXFifoProtectCanceler();
};

}

#endif
