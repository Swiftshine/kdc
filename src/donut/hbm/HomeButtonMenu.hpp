#ifndef DONUT_HBM_HOMEBUTTONMENU_HPP
#define DONUT_HBM_HOMEBUTTONMENU_HPP

#include <types.h>

namespace hbm {

class HomeButtonMenu {
public:
    HomeButtonMenu(bool);
    ~HomeButtonMenu();
private:
    STRUCT_FILL(0x5E0);
};

}

#endif
