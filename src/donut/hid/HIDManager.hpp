#ifndef DONUT_HID_HIDMANAGER_HPP
#define DONUT_HID_HIDMANAGER_HPP

#include <types.h>

namespace hid {

class HIDManager {
public:
    HIDManager();
    ~HIDManager();
private:
    STRUCT_FILL(0x15A8);
};

}

#endif
