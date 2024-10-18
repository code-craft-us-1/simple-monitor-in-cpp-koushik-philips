#include <set>
#include <string>
#include "./pulserate.h"

using VitalConstants::PULSE_LIMIT_LOW;
using VitalConstants::PULSE_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;
extern std::string getPulseRateCategoryMessage(int category);

//  Singleton
VitalBaseline& createPulseRateBaseline(float lowLimit, float highLimit,
                                       float toleranceLimit)
{
    static VitalBaseline commonBaseline(lowLimit, highLimit,
        toleranceLimit);
    return commonBaseline;
}

PulseRate::PulseRate(float pulserate) :
    Vital(pulserate,
        createPulseRateBaseline(PULSE_LIMIT_LOW, PULSE_LIMIT_HIGH, TOLERANCE_PERCENT)) {
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string PulseRate::getMessage(int category) const {
    return getPulseRateCategoryMessage(category);
}
