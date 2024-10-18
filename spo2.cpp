#include <set>
#include <string>
#include "./spo2.h"

using VitalConstants::SPO2_LIMIT_LOW;
using VitalConstants::SPO2_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;
extern std::string getSPO2CategoryMessage(int category);

//  Singleton
VitalBaseline& createSPO2Baseline(float lowLimit, float highLimit,
                                  float toleranceLimit)
{
    static VitalBaseline commonBaseline(lowLimit, highLimit,
        toleranceLimit);
    return commonBaseline;
}

SPO2::SPO2(float spo2) :
    Vital(spo2,
        createSPO2Baseline(SPO2_LIMIT_LOW, SPO2_LIMIT_HIGH, TOLERANCE_PERCENT)) {
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string SPO2::getMessage(int category) const {
    return getSPO2CategoryMessage(category);
}
