#ifndef DONUT_SCN_STEP_HERO_HERO_HPP
#define DONUT_SCN_STEP_HERO_HERO_HPP

#include "scn/step/common/Param.hpp"

namespace scn { namespace step { namespace hero {
    class Param { // todo: put this in its own file
    public:
        common::Param* indiviKirby() const;
        common::Param* indiviMeta() const;
        common::Param* indiviDedede() const;
        common::Param* indiviDee() const;
    };

    enum Kind {
        KIND_KIRBY      = 0,
        KIND_KIRBY_1    = 0,
        KIND_KIRBY_2    = 1,
        KIND_KIRBY_3    = 2,
        KIND_KIRBY_4    = 3,
        KIND_META       = 4,
        KIND_DEDEDE     = 5,
        KIND_DEE        = 6,
    };

    class Hero {
    public:
        Param* param() const;
        Kind kind() const; // code merged
    };
}}}

#endif
