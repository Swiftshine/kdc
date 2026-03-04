#ifndef DONUT_SCN_STEP_ENEMY_PARAM_HPP
#define DONUT_SCN_STEP_ENEMY_PARAM_HPP

#include "param/JITParam.hpp"

using param::JITParam;


// i'm not doing this manually
// and i doubt hal did either

#define ENEMY_NAMESPACE_PARAM(enemy_name) \
namespace scn { namespace step { namespace enemy { namespace enemy_name { \
    struct Param { }; \
}}}}

#define DECL_GET_ENEMY_PARAM(enemy_name) \
    enemy_name::Param* enemy_name() const

ENEMY_NAMESPACE_PARAM(common)
ENEMY_NAMESPACE_PARAM(sirkibble)
ENEMY_NAMESPACE_PARAM(brontoburt)
ENEMY_NAMESPACE_PARAM(waddledee)
ENEMY_NAMESPACE_PARAM(bladeknight)
ENEMY_NAMESPACE_PARAM(cappy)
ENEMY_NAMESPACE_PARAM(hothead)
ENEMY_NAMESPACE_PARAM(knucklejoe)
// ENEMY_NAMESPACE_PARAM(puppetdee)
// ENEMY_NAMESPACE_PARAM(armordee)
ENEMY_NAMESPACE_PARAM(como)
ENEMY_NAMESPACE_PARAM(gordo)
ENEMY_NAMESPACE_PARAM(whippy)
ENEMY_NAMESPACE_PARAM(shotzo)
ENEMY_NAMESPACE_PARAM(leafan)
ENEMY_NAMESPACE_PARAM(waddledoo)
ENEMY_NAMESPACE_PARAM(bouncy)
ENEMY_NAMESPACE_PARAM(sparky)
ENEMY_NAMESPACE_PARAM(needlous)
ENEMY_NAMESPACE_PARAM(broomhatter)
ENEMY_NAMESPACE_PARAM(scarfy)
ENEMY_NAMESPACE_PARAM(nruff)
ENEMY_NAMESPACE_PARAM(flamer)
ENEMY_NAMESPACE_PARAM(watergalbo)
ENEMY_NAMESPACE_PARAM(rocky)
ENEMY_NAMESPACE_PARAM(poppybrojr)
ENEMY_NAMESPACE_PARAM(noddy)
ENEMY_NAMESPACE_PARAM(cerulean)
ENEMY_NAMESPACE_PARAM(blipper)
ENEMY_NAMESPACE_PARAM(gigatzo)
ENEMY_NAMESPACE_PARAM(sisterbound)
ENEMY_NAMESPACE_PARAM(rollball)
ENEMY_NAMESPACE_PARAM(mumbies)
ENEMY_NAMESPACE_PARAM(parasoldee)
ENEMY_NAMESPACE_PARAM(kabu)
ENEMY_NAMESPACE_PARAM(parasoldoo)
ENEMY_NAMESPACE_PARAM(foley)
ENEMY_NAMESPACE_PARAM(juckle)
ENEMY_NAMESPACE_PARAM(bowby)
ENEMY_NAMESPACE_PARAM(owgulf)
ENEMY_NAMESPACE_PARAM(degout)
ENEMY_NAMESPACE_PARAM(sheld)
ENEMY_NAMESPACE_PARAM(lanzer)
ENEMY_NAMESPACE_PARAM(chilly)
ENEMY_NAMESPACE_PARAM(tsukikage)
ENEMY_NAMESPACE_PARAM(gemra)
ENEMY_NAMESPACE_PARAM(sodory)
ENEMY_NAMESPACE_PARAM(searches)
ENEMY_NAMESPACE_PARAM(pierce)
ENEMY_NAMESPACE_PARAM(elec)
ENEMY_NAMESPACE_PARAM(snowl)
ENEMY_NAMESPACE_PARAM(sun)
ENEMY_NAMESPACE_PARAM(sandbag)
ENEMY_NAMESPACE_PARAM(stareffect)
// ENEMY_NAMESPACE_PARAM(cappyhat)
ENEMY_NAMESPACE_PARAM(whispyapple)
ENEMY_NAMESPACE_PARAM(parasol)
ENEMY_NAMESPACE_PARAM(dubiorjr)
ENEMY_NAMESPACE_PARAM(poppybrojrbomb)
ENEMY_NAMESPACE_PARAM(zankibblecutter)
ENEMY_NAMESPACE_PARAM(bonkersbomb)
ENEMY_NAMESPACE_PARAM(dubiorspark)
ENEMY_NAMESPACE_PARAM(mbossdead)

namespace scn { namespace step { namespace enemy {
class Param {
public:
    Param();
    static void exception(u32); // weak

    DECL_GET_ENEMY_PARAM(common);
    DECL_GET_ENEMY_PARAM(sirkibble);
    DECL_GET_ENEMY_PARAM(brontoburt);
    DECL_GET_ENEMY_PARAM(waddledee);
    DECL_GET_ENEMY_PARAM(bladeknight);
    DECL_GET_ENEMY_PARAM(cappy);
    DECL_GET_ENEMY_PARAM(hothead);
    DECL_GET_ENEMY_PARAM(knucklejoe);
    // DECL_GET_ENEMY_PARAM(puppetdee);
    // DECL_GET_ENEMY_PARAM(armordee);
    DECL_GET_ENEMY_PARAM(como);
    DECL_GET_ENEMY_PARAM(gordo);
    DECL_GET_ENEMY_PARAM(whippy);
    DECL_GET_ENEMY_PARAM(shotzo);
    DECL_GET_ENEMY_PARAM(leafan);
    DECL_GET_ENEMY_PARAM(waddledoo);
    DECL_GET_ENEMY_PARAM(bouncy);
    DECL_GET_ENEMY_PARAM(sparky);
    DECL_GET_ENEMY_PARAM(needlous);
    DECL_GET_ENEMY_PARAM(broomhatter);
    DECL_GET_ENEMY_PARAM(scarfy);
    DECL_GET_ENEMY_PARAM(nruff);
    DECL_GET_ENEMY_PARAM(flamer);
    DECL_GET_ENEMY_PARAM(watergalbo);
    DECL_GET_ENEMY_PARAM(rocky);
    DECL_GET_ENEMY_PARAM(poppybrojr);
    DECL_GET_ENEMY_PARAM(noddy);
    DECL_GET_ENEMY_PARAM(cerulean);
    DECL_GET_ENEMY_PARAM(blipper);
    DECL_GET_ENEMY_PARAM(gigatzo);
    DECL_GET_ENEMY_PARAM(sisterbound);
    DECL_GET_ENEMY_PARAM(rollball);
    DECL_GET_ENEMY_PARAM(mumbies);
    DECL_GET_ENEMY_PARAM(parasoldee);
    DECL_GET_ENEMY_PARAM(kabu);
    DECL_GET_ENEMY_PARAM(parasoldoo);
    DECL_GET_ENEMY_PARAM(foley);
    DECL_GET_ENEMY_PARAM(juckle);
    DECL_GET_ENEMY_PARAM(bowby);
    DECL_GET_ENEMY_PARAM(owgulf);
    DECL_GET_ENEMY_PARAM(degout);
    DECL_GET_ENEMY_PARAM(sheld);
    DECL_GET_ENEMY_PARAM(lanzer);
    DECL_GET_ENEMY_PARAM(chilly);
    DECL_GET_ENEMY_PARAM(tsukikage);
    DECL_GET_ENEMY_PARAM(gemra);
    DECL_GET_ENEMY_PARAM(sodory);
    DECL_GET_ENEMY_PARAM(searches);
    DECL_GET_ENEMY_PARAM(pierce);
    DECL_GET_ENEMY_PARAM(elec);
    DECL_GET_ENEMY_PARAM(snowl);
    DECL_GET_ENEMY_PARAM(sun);
    DECL_GET_ENEMY_PARAM(sandbag);
    DECL_GET_ENEMY_PARAM(stareffect);
    // DECL_GET_ENEMY_PARAM(cappyhat);
    DECL_GET_ENEMY_PARAM(whispyapple);
    DECL_GET_ENEMY_PARAM(parasol);
    DECL_GET_ENEMY_PARAM(dubiorjr);
    DECL_GET_ENEMY_PARAM(poppybrojrbomb);
    DECL_GET_ENEMY_PARAM(zankibblecutter);
    DECL_GET_ENEMY_PARAM(bonkersbomb);
    DECL_GET_ENEMY_PARAM(dubiorspark);
    DECL_GET_ENEMY_PARAM(mbossdead);

private:
    // straying from the m prefix here due to macros
    /* 0x000 */ JITParam common_;
    /* 0x010 */ JITParam sirkibble_;
    /* 0x020 */ JITParam brontoburt_;
    /* 0x030 */ JITParam waddledee_;
    /* 0x040 */ JITParam bladeknight_;
    /* 0x050 */ JITParam cappy_;
    /* 0x060 */ JITParam hothead_;
    /* 0x070 */ JITParam knucklejoe_;
    /* 0x080 */ JITParam puppetdee_;
    /* 0x090 */ JITParam armordee_;
    /* 0x0A0 */ JITParam como_;
    /* 0x0B0 */ JITParam gordo_;
    /* 0x0C0 */ JITParam whippy_;
    /* 0x0D0 */ JITParam shotzo_;
    /* 0x0E0 */ JITParam leafan_;
    /* 0x0F0 */ JITParam waddledoo_;
    /* 0x100 */ JITParam bouncy_;
    /* 0x110 */ JITParam sparky_;
    /* 0x120 */ JITParam needlous_;
    /* 0x130 */ JITParam broomhatter_;
    /* 0x140 */ JITParam scarfy_;
    /* 0x150 */ JITParam nruff_;
    /* 0x160 */ JITParam flamer_;
    /* 0x170 */ JITParam watergalbo_;
    /* 0x180 */ JITParam rocky_;
    /* 0x190 */ JITParam poppybrojr_;
    /* 0x1A0 */ JITParam noddy_;
    /* 0x1B0 */ JITParam cerulean_;
    /* 0x1C0 */ JITParam blipper_;
    /* 0x1D0 */ JITParam gigatzo_;
    /* 0x1E0 */ JITParam sisterbound_;
    /* 0x1F0 */ JITParam rollball_;
    /* 0x200 */ JITParam mumbies_;
    /* 0x210 */ JITParam parasoldee_;
    /* 0x220 */ JITParam kabu_;
    /* 0x230 */ JITParam parasoldoo_;
    /* 0x240 */ JITParam foley_;
    /* 0x250 */ JITParam juckle_;
    /* 0x260 */ JITParam bowby_;
    /* 0x270 */ JITParam owgulf_;
    /* 0x280 */ JITParam degout_;
    /* 0x290 */ JITParam sheld_;
    /* 0x2A0 */ JITParam lanzer_;
    /* 0x2B0 */ JITParam chilly_;
    /* 0x2C0 */ JITParam tsukikage_;
    /* 0x2D0 */ JITParam gemra_;
    /* 0x2E0 */ JITParam sodory_;
    /* 0x2F0 */ JITParam searches_;
    /* 0x300 */ JITParam pierce_;
    /* 0x310 */ JITParam elec_;
    /* 0x320 */ JITParam snowl_;
    /* 0x330 */ JITParam sun_;
    /* 0x340 */ JITParam sandbag_;
    /* 0x350 */ JITParam stareffect_;
    /* 0x360 */ JITParam cappyhat_;
    /* 0x370 */ JITParam whispyapple_;
    /* 0x380 */ JITParam parasol_;
    /* 0x390 */ JITParam dubiorjr_;
    /* 0x3A0 */ JITParam poppybrojrbomb_;
    /* 0x3B0 */ JITParam zankibblecutter_;
    /* 0x3C0 */ JITParam bonkersbomb_;
    /* 0x3D0 */ JITParam dubiorspark_;
    /* 0x3E0 */ JITParam mbossdead_;
};

}}}

#endif
