#include <set>
#include <string>
#include "./pulserate.h"

extern std::string getPulseRateCategoryMessage(int category);

namespace {
    constexpr float PULSE_LIMIT_HIGH = 100;
    constexpr float PULSE_LIMIT_LOW = 60;
    constexpr float PULSE_TOLERANCE_PERCENT = 1.5;
}

PulseRate::PulseRate(float pulserate) :
    Vital(pulserate,
        createBaseline<PulseRateBaseline>(PULSE_LIMIT_LOW, PULSE_LIMIT_HIGH, TOLERANCE_PERCENT)) {
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string PulseRate::getMessage(int category) const {
    return getPulseRateCategoryMessage(category);
}
