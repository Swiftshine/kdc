#ifndef DONUT_APP_RESIDENTFILE_HPP
#define DONUT_APP_RESIDENTFILE_HPP

#include <types.h>

namespace app {

class ResidentFile {
public:
    ResidentFile();
    ~ResidentFile();
private:
    STRUCT_FILL(0x3D0);
};

}

#endif
