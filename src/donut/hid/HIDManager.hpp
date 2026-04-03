#ifndef DONUT_HID_HIDMANAGER_HPP
#define DONUT_HID_HIDMANAGER_HPP

#include <donut/hid/Button.hpp>

#define MAX_HID_COUNT 4

namespace hid {

// todo: move these to their own headers

class HIDAccessor {
public:
    Button button() const;
};

class HIDManager {
public:
    HIDManager();
    ~HIDManager();

    void updateGame();
    void resetButtonConvertKind();
    void updateMaster();
    HIDAccessor& gameHID(u32 index) const;

    void updateDebug() DONT_INLINE { }
private:
    STRUCT_FILL(0x15A8);
};

}

#endif
