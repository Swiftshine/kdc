#ifndef DONUT_GFX_EFBTOLETTERBOX_HPP
#define DONUT_GFX_EFBTOLETTERBOX_HPP

#include <donut/gfx/TexBuffer.hpp>

namespace gfx {

class GameScreen;

class EFBToLetterBox {
public:
    EFBToLetterBox(GameScreen&);
    ~EFBToLetterBox();
    void draw();

    //NOTE: Merged into util::Delegate<Fv_v,64>::DelegateHeap::allocatorAlloc(unsigned long, long)
    TexBuffer texBuffer();
private:
    /* 0x0 */ GameScreen* mGameScreen;
    /* 0x4 */ TexBuffer mBuffer;
};
}

#endif
