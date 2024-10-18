#include <set>
#include <string>
#include "./pulserate.h"

using VitalConstants::PULSE_LIMIT_LOW;
using VitalConstants::PULSE_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;
extern std::string getPulseRateCategoryMessage(int category);

PulseRate::PulseRate(float pulserate) :
    Vital(PULSE_LIMIT_LOW, PULSE_LIMIT_HIGH,
        TOLERANCE_PERCENT, pulserate) {
    initLevels();
}

std::set<int> PulseRate::collectInvalidCategories() const {
    std::set<int> invalidCategoies;
    invalidCategoies.insert(static_cast<int>(Category::BRADYCARDIA));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_BRADY));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_TACHY));
    invalidCategoies.insert(static_cast<int>(Category::TACHYCARDIA));
    return invalidCategoies;
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string PulseRate::getMessage(int category) const {
    return getPulseRateCategoryMessage(category);
}
