#ifndef DONUT_HID_BUTTON_HPP
#define DONUT_HID_BUTTON_HPP

#include <types.h>

namespace hid {

class Button {
public:
    //NOTE: Merged into GKI_init_timer_list
    Button();

    void update(u32 buttonFlags);

    bool isHold(u32 buttonFlags) const;
    bool isTrigger(u32 buttonFlags) const;
    //NOTE: Unused lol
    bool isRelease(u32 buttonFlags) const;

    //NOTE: Merged into GKI_getfirst
    u32 hold() const;
    //NOTE: Merged into nw4r::snd::detail::AxManager::GetZeroBufferAddress()
    u32 trigger() const;
    //NOTE: Merged into ARCGetLength
    u32 release() const;

private:
    /* 0x0 */ u32 mHold;
    /* 0x4 */ u32 mTrigger;
    /* 0x8 */ u32 mRelease;
};

}

#endif
