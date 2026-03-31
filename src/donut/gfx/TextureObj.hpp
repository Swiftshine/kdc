#ifndef DONUT_GFX_TEXTURE_OBJECT_HPP
#define DONUT_GFX_TEXTURE_OBJECT_HPP

#include <types.h>
#include <revolution/GX.h>

namespace gfx {
    class TextureObj {
    public:
        TextureObj() DECOMP_DONT_INLINE {}
        //TODO: This needs to be linked into EasyTex3D
        /* 0x0 */ virtual ~TextureObj() DECOMP_DONT_INLINE {}

        //https://decomp.me/scratch/5Td3o
        GXTexObj* texObj() const {
            GXTexObj* texObj;
            for (int i = 4; i != 0; i--) {

                texObj->dummy[2] = mGXTexObj.dummy[2];
            }
            return texObj;
        }

        /* 0x4 */ GXTexObj mGXTexObj;
    };
}

#endif
