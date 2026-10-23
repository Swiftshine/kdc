#ifndef DONUT_SCN_STEP_HERO_INVINCIBLE_HPP_
#define DONUT_SCN_STEP_HERO_INVINCIBLE_HPP_

#include <GX/GXTypes.h>

#include "scn/step/Hero/Hero.hpp"
#include "scn/step/chara/Invincible.hpp"

// clang-format off
namespace scn { namespace step { namespace hero {

class Invincible
{
public:
    Invincible(Hero &rHero);
    void update();
    void set(u32 frames);
    void setNoFlash(u32 frames);
    void setPerm();
    void setPermNoFlash();
    void unsetPerm();
    void setMighty();
    void setMighty(u32 frames);
    void setMightyAfter(u32 frames);
    void clearMighty();
    void clear();
    bool getFlashOp() const;
    u32 getInvincibleFrame() const;
    void setBodyCollStateNormalIfNotMighty();
    void requestMightyEffect();
    void releaseMightyEffect();
private:
    /* 0x00 */ Hero *mHero;
    /* 0x04 */ chara::Invincible mInvincible;
    /* 0x10 */ bool mUnk10; // intangible flash
    /* 0x11 */ bool mUnk11; // candy mighty effect
    /* 0x12 */ bool mUnk12; // candy sparkling effect
    /* 0x14 */ u32 mUnk14; // candy timer
    /* 0x18 */ u32 mUnk18; // candy end timer
    /* 0x1C */ u32 mUnk1C; // rainbow cycle
    /* 0x20 */ _GXColor mRGB; 
    /* 0x24 */ bool mUnk24;
};

}}}
// clang-format on

#endif
