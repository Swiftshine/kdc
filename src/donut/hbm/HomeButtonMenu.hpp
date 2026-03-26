#ifndef DONUT_HBM_HOMEBUTTONMENU_HPP
#define DONUT_HBM_HOMEBUTTONMENU_HPP

#include <types.h>

namespace hbm {

class HomeButtonMenu {
public:
    HomeButtonMenu(bool);
    ~HomeButtonMenu();

    bool isOpened() const;
    bool getIgnore() const;
    bool isEnable() const;
    void startDisableIconAnimIfPossible();
    bool isSetupFinished() const;
    void open();
    void process(bool);
    void display();
private:
    STRUCT_FILL(0x5E0);
};

}

#endif
