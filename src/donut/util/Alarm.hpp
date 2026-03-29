#ifndef DONUT_UTIL_ALARM_HPP
#define DONUT_UTIL_ALARM_HPP

#include <hel/common/ExplicitSingleton.hpp>
#include <revolution/OS.h>

namespace util {

class Alarm : public hel::common::ExplicitSingleton<Alarm> {
public:
    DECL_EXPLICIT_SINGLETON(Alarm)

    Alarm();
    virtual ~Alarm();

    void init();
    void final();

private:
    /* 0x8 */ OSAlarm mAlarm;
};
}

#endif
