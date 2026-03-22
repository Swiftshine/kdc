#ifndef DONUT_APP_PERFORMANCECONTROLLER_HPP
#define DONUT_APP_PERFORMANCECONTROLLER_HPP

#include <types.h>

namespace app {

class PerformanceController {
public:
    PerformanceController();
    ~PerformanceController();
private:
    STRUCT_FILL(0x14);
};

}

#endif
