#ifndef DONUT_APP_NANDERRORMENU_HPP
#define DONUT_APP_NANDERRORMENU_HPP

#include <types.h>

namespace app {

class ResidentFile;

class NANDErrorMenu {
public:
    NANDErrorMenu(ResidentFile&);
    ~NANDErrorMenu();
private:
    STRUCT_FILL(0x68);
};

}

#endif
