#ifndef DONUT_APP_HIDERRORMENU_HPP
#define DONUT_APP_HIDERRORMENU_HPP

#include <types.h>

namespace app {

class HIDErrorMenu {
public:
    HIDErrorMenu();
    ~HIDErrorMenu();
private:
    STRUCT_FILL(0x70);
};

} // app

#endif
