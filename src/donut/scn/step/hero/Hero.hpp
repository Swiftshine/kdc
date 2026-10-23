#ifndef DONUT_SCN_STEP_HERO_HERO_HPP
#define DONUT_SCN_STEP_HERO_HERO_HPP

#include "mem/ExplicitScopedPtr.hpp"
#include "scn/step/common/Param.hpp"
#include "scn/step/hero/Kind.hpp"

// clang-format off
namespace scn { namespace step { namespace hero {
    class Param { // todo: put this in its own file
    public:
        common::Param* common() const;
        common::Param* indiviKirby() const;
        common::Param* indiviMeta() const;
        common::Param* indiviDedede() const;
        common::Param* indiviDee() const;
    };

    class Hero {
    public:
        Param* param() const;
        // NOTE: Is merged into mcoll::detail::CollidedDetectionInfo::collideTargetIndex() const
        Kind kind() const;
    private:
        STRUCT_FILL(0x70);
        mem::ExplicitScopedPtr<Param*> mParam;
        STRUCT_FILL(0xE8 - 0x78);
    };
}}}
// clang-format on

#endif
