#ifndef DONUT_UTIL_ALARM_HPP
#define DONUT_UTIL_ALARM_HPP

#include <types.h>

namespace util {

class Alarm {
public:
    Alarm();
    ~Alarm();
private:
    STRUCT_FILL(8);
};

}

#endif
