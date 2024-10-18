#include "./spo2.h"

using VitalConstants::SPO2_LIMIT_LOW;
using VitalConstants::SPO2_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;

SPO2::SPO2(float spo2) :
    Vital(SPO2_LIMIT_LOW, SPO2_LIMIT_HIGH,
          TOLERANCE_PERCENT, spo2) {
    initLevels();
}

std::set<int> SPO2::collectInvalidCategories() const {
    std::set<int> invalidCategoies;
    invalidCategoies.insert(static_cast<int>(Category::HYPOAXEMIA));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_HYPOAXEMIA));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_HYPEROAXEMIA));
    invalidCategoies.insert(static_cast<int>(Category::HYPEROAXEMIA));
    return invalidCategoies;
}
std::string SPO2::getMessage(int category) const {
    auto spo2category = static_cast<Category>(category);
    switch (spo2category) {
    case Category::HYPOAXEMIA:          return "Hypoaxemia : Oxygen Saturation out of range!\n";
    case Category::NEAR_HYPOAXEMIA:     return "Warning: Approaching hypoaxemia\n";
    case Category::NORMAL:              return "Normal Temperature\n";
    case Category::NEAR_HYPEROAXEMIA:   return "Warning: Approaching hyperoaxemia\n";
    case Category::HYPEROAXEMIA:        return "Hyperoaxemia : Oxygen Saturation out of range!\n";
    default:
        break;
    }
    return "Error";
}
