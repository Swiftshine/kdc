#ifndef DONUT_GFX_EFBTOLETTERBOX_HPP
#define DONUT_GFX_EFBTOLETTERBOX_HPP

#include <types.h>

namespace gfx {

class GameScreen;

class EFBToLetterBox {
public:
    EFBToLetterBox(GameScreen&);
    ~EFBToLetterBox();
private:
    STRUCT_FILL(0x18);
};
}

#endif
