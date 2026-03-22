#ifndef DONUT_NAND_NANDMANAGER_HPP
#define DONUT_NAND_NANDMANAGER_HPP

#include <types.h>

namespace nand {

class NandManager {
public:
    NandManager();
    ~NandManager();

private:
    STRUCT_FILL(0x508);
};

}

#endif
