#ifndef DONUT_GFX_FULL_SCREEN_PLATE_HPP
#define DONUT_GFX_FULL_SCREEN_PLATE_HPP

#include <revolution/GX.h>


namespace gfx {
    class FullScreenPlate {
    public:
        FullScreenPlate(const GXColor& rColor);

        void draw() const;
        //NOTE: Merged into _GXColor::operator=(const _GXColor&)
        void setColor(const GXColor& rColor);
        //NOTE: Merged into homebutton::Controller::setSpeakerVol(float)
        void setAlpha(f32 alpha);

        /* 0x0 */ GXColor mColor;
        /* 0x4 */ f32 mAlpha;
    };
}

#endif
