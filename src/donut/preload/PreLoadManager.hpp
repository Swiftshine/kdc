#ifndef DONUT_PRELOAD_PRELOADMANAGER_HPP
#define DONUT_PRELOAD_PRELOADMANAGER_HPP

#include <types.h>

namespace preload {

class PreLoadManager {
public:
    PreLoadManager();
    ~PreLoadManager();
private:
    STRUCT_FILL(0xBB64);
};

}

#endif
