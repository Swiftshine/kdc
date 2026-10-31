#ifndef DONUT_SCN_STEP_CHARA_HITSTOP_HPP
#define DONUT_SCN_STEP_CHARA_HITSTOP_HPP

#include <types.h>

/* clang-format off */
namespace scn { namespace step { namespace chara {

class IHitStopCallBack {
public:
    /* 0x0 */ virtual void Unk0() = 0;
    /* 0x4 */ virtual void Unk4() = 0;
    /* 0x8 */ virtual void Unk8() = 0;
    /* 0xC */ virtual void UnkC() = 0;
    /* 0x10 */ virtual void Unk10() = 0;
};

class HitStop {
public:
    HitStop();
    HitStop(IHitStopCallBack& callback);

    void update();
    void set(u32 frame);
    void setSoft(u32 frame);
    void clear();
private:
    /* 0x0 */ s32 mFrame;
    /* 0x4 */ s32 mFramePre; // Name is a rough guess since it's never actually used for anything.
    /* 0x8 */ bool m_8;
    /* 0x9 */ bool mIsSoft;
    /* 0xA */ bool mIsLocked;
    /* 0xC */ IHitStopCallBack* mCallback;
};

}}}

#endif
