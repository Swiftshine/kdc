#pragma peephole off
#include <donut/gfx/TPLTexture.hpp>
#include <revolution/TPL.h>

using gfx::TPLTexture;

//Note: this is originally an unused function, however it seems to either A. use texObj directly or B. use TextureObj->load (another unused function)
//In order to place texObj into this TU
TPLTexture::TPLTexture(const char* pArg1)
    : mFileAccessor()
{
    texObj();
}

TPLTexture::TPLTexture(void* pArg1)
    : mFileAccessor()
{
    init(pArg1);
}

void TPLTexture::init(void* pArg1) {
    TPLPalette* palette = (TPLPalette*)pArg1;

    if ((u32)(palette->descriptorArray) < 0x80000000) {
        TPLBind(palette);
    }
    TPLGetGXTexObjFromPalette(palette, &mGXTexObj, 0);
}
