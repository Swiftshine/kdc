#ifndef DONUT_HID_HIDMANAGER_HPP
#define DONUT_HID_HIDMANAGER_HPP

#include <types.h>

namespace hid {

class HIDManager {
public:
    HIDManager();
    ~HIDManager();

    void updateGame();
    void resetButtonConvertKind();
    void updateMaster();

    void updateDebug() DONT_INLINE { }
private:
    STRUCT_FILL(0x15A8);
};

}

#endif
