#include "./pulserate.h"

using VitalConstants::PULSE_LIMIT_LOW;
using VitalConstants::PULSE_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;

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
std::string PulseRate::getMessage(int category) const {
    auto pulseRateCategory = static_cast<Category>(category);
    switch (pulseRateCategory) {
    case Category::BRADYCARDIA: return "Bradycardia : Pulse Rate is out of range!\n";
    case Category::NEAR_BRADY:  return "Warning: Approaching bradycardia\n";
    case Category::NORMAL:      return "Normal pule rate\n";
    case Category::NEAR_TACHY:  return "Warning: Approaching tachycardia\n";
    case Category::TACHYCARDIA: return "Tachycardia : Pulse Rate is out of range!\n";
    default:
        break;
    }
    return "Error";
}
