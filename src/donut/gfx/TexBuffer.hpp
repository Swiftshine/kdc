#ifndef DONUT_GFX_TEXTURE_BUFFER_HPP
#define DONUT_GFX_TEXTURE_BUFFER_HPP

#include <revolution/GX.h>
#include <donut/mem/DataBlock.hpp>

namespace gfx {
    class TexBuffer {
    public:
        TexBuffer(mem::IAllocator& rAllocator, u16 width, u16 height, GXTexFmt format);
        ~TexBuffer();

        //NOTE: Merged into mem::DataBlock::block()
        mem::MemBlock block() const;

        //NOTE: merged into nw4r::ef::MemoryManagerTmp<nw4r::ef::Particle>::GetNumFreeObject() const
        u16 width() const;
        //NOTE: merged into GXGetTexObjUserData
        GXTexFmt format() const;

        u16 height() const;

        /* 0x00 */ mem::DataBlock mDataBlock;
        /* 0x0C */ u16 mWidth;
        /* 0x0E */ u16 mHeight;
        /* 0x10 */ GXTexFmt mFormat;
    };
}

#endif
