#ifndef DONUT_GFX_TPL_TEXTURE_PLATE_HPP
#define DONUT_GFX_TPL_TEXTURE_PLATE_HPP

#include <nw4r/ut.h>
#include <donut/gfx/TPLTexture.hpp>

namespace hel { namespace math {
    class Vector2;
} };

namespace gfx {
    class TPLTexturePlate {
    public:
        TPLTexturePlate(void*);
        ~TPLTexturePlate();

        void setAlpha(u8 alpha);
        void drawForHomeButtonIcon() const;
        void init();
        void drawCore() const;
        void setupTevRenderModePlane() const;
        void setPos(const hel::math::Vector2& rPosition);

        /* 0x00 */ TPLTexture mTPLTexture;
        /* 0x28 */ s32 m_28;
        /* 0x2C */ GXTexObj mTexObj;
        /* 0x4C */ nw4r::ut::Rect m_4C;
        /* 0x5C */ Mtx mPos;
        /* 0x8C */ u8 mAlpha;
        /* 0x8D */ bool mInited;
    };
}

#endif
