#pragma peephole off
#include <donut/util/Alarm.hpp>
#include <donut/util/DisableInterrupts.hpp>

using util::Alarm;
using util::DisableInterrupts;

namespace {
    //https://decomp.me/scratch/seCTg
    static s64 T_PERIOD;
    void t_handler(OSAlarm* pAlarm, OSContext* pContext) {}
}

Alarm::Alarm() {
    init();
    Instance = this;
}

Alarm::~Alarm() {
    Instance = nullptr;
    final();
}

//https://decomp.me/scratch/knUNk
void Alarm::init() {
    OSCreateAlarm(mAlarm);
    OSSetPeriodicAlarm(mAlarm, T_PERIOD, T_PERIOD, t_handler);
}

//https://decomp.me/scratch/ArudS
void Alarm::final() {
    DisableInterrupts interrupts;

    OSCancelAlarm(mAlarm);
}
