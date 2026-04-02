#ifndef DONUT_GFX_TEXTURE_OBJECT_HPP
#define DONUT_GFX_TEXTURE_OBJECT_HPP

#include <types.h>
#include <revolution/GX.h>

namespace gfx {
    class TextureObj {
    public:
        //TODO: Could this actually be defined in TPLTexture.cpp like the binary says or is it weak?
        TextureObj() DECOMP_DONT_INLINE {}

        //TODO: This needs to be linked into EasyTex3D

        /* 0x8 */ virtual ~TextureObj() DECOMP_DONT_INLINE {}

        //TODO: Could this actually be defined in TPLTexture.cpp like the binary says or is it weak?
        GXTexObj texObj() const DECOMP_DONT_INLINE {
            return mGXTexObj;
        }

        /* 0x4 */ GXTexObj mGXTexObj;
    };
}

#endif
