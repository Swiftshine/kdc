#ifndef DONUT_APP_AUTORESETTIMER_HPP
#define DONUT_APP_AUTORESETTIMER_HPP

#include <types.h>

namespace app {

class AutoResetTimer {
public:
    AutoResetTimer();

    void update();
private:
    STRUCT_FILL(0xC);
};
}

#endif
