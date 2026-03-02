#ifndef DONUT_SCN_STEP_HERO_INDIVIUTIL_HPP
#define DONUT_SCN_STEP_HERO_INDIVIUTIL_HPP

#include "scn/step/common/Param.hpp"
#include "scn/step/hero/Hero.hpp"

#include <hel/math/Vector3.hpp>

namespace scn { namespace step { namespace hero {

class NodeAttach {
public:
    void setOffset(const hel::math::Vector3& rOffset);
    void setRotate(const hel::math::Vector3& rRotate);
    void setScale(float scale);
};

struct NodeAttachParam {
    /* 0x00 */ hel::math::Vector3 mOffset;
    /* 0x0C */ hel::math::Vector3 mRotate;
    /* 0x18 */ float mScale;
};

class IndiviUtil {
public:
    static common::Param* Param(const Hero& rHero);
    static float CenterOffset(Kind kind);
    static void InitNodeAttach(NodeAttach& rNodeAttach, Kind kind);
    static bool IsKirby(Kind kind);
    static bool IsMeta(Kind kind);
    static bool IsDedede(Kind kind);
    static bool IsDee(Kind kind);
    static bool CanHover(Kind kind);

    void VacuumAttackerOffset();
private:
    /* 0x0 */ float m_0;
    /* 0x4 */ float m_4;
};

} // hero
} // step
} // scn

#endif
