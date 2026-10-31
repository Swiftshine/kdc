#ifndef DONUT_SCN_STEP_CHARA_HITPOINT_HPP
#define DONUT_SCN_STEP_CHARA_HITPOINT_HPP

#include <types.h>

/* clang-format off */
namespace scn { namespace step { namespace chara {

class HitPoint {
public:
    HitPoint();

    bool isFull() const;
    bool isDeadBentZero() const;
    void init(u32 points);
    void initDeadBent(u32 deadBent);
    void dec(u32 amount);
    void inc(u32 amount);
    void set(u32 points);
    void decDeadBent(u32 amount);
    void setMin(u32 min);
    float rate() const;
private:
    /* 0x0 */ u32 mPoints;
    /* 0x4 */ u32 mMax;
    /* 0x8 */ u32 mMin;
    /* 0xC */ u32 mDeadBent;
    /* 0x10 */ u32 mPrevPoints;
    /* 0x14 */ u32 m_14;
};

}}}

#endif
