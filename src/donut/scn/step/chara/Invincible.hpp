#ifndef DONUT_SCN_STEP_CHARA_INVINCIBLE_HPP
#define DONUT_SCN_STEP_CHARA_INVINCIBLE_HPP

#include <types.h>

/* clang-format off */
namespace scn { namespace step { namespace chara {

class Invincible
{
public:
    Invincible();

    void update();

    bool isInvincible() const;
    void set(u32 frames);
    void clear();

    void setPerm();
    // Gets merged into scn::step::enemy::SuperStop::onSuperStopStarted(const scn::step::spstop::Manager&)
    void unsetPerm();
    // Gets merged into nururi::Nururi::isValid() const
    bool isPerm() const;

    // Gets merged into scn::step::enemy::mumbies::Custom::onCaptured()
    void setMighty();
    void unsetMighty();
    bool isMighty() const;

    // Gets merged into GKI_getfirst
    u32 getFrame() const;

    u32 getFlashAlpha() const;
    void updateFrame();

public:
    /* 0x00 */ u32 mFrame;
    /* 0x04 */ u32 mAnimFrame;
    /* 0x08 */ bool mIsPerm;
    /* 0x09 */ bool mIsMighty;
};

}}}

/* clang-format on */

#endif
