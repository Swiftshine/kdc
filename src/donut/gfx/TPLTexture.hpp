#ifndef DONUT_GFX_TPL_TEXTURE_HPP
#define DONUT_GFX_TPL_TEXTURE_HPP

#include <donut/gfx/TextureObj.hpp>
#include <donut/util/PlacementNew.hpp>
#include <donut/file/FileAccessor.hpp>

namespace gfx {
    class TPLTexture : public TextureObj {
    public:
        TPLTexture(void*);
        //Unused in the binary, however we need it so that TextureObj::texObj is called
        TPLTexture(const char*);

        //TODO: This needs to be linked into EasyTex3D
        /* 0x8 */ virtual ~TPLTexture() {}
        void init(void*);


        /* 0x24 */ util::PlacementNew<file::FileAccessor> mFileAccessor;
    };
}

#endif
