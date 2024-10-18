#include <set>
#include <string>
#include "./spo2.h"

using VitalConstants::SPO2_LIMIT_LOW;
using VitalConstants::SPO2_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;
extern std::string getSPO2CategoryMessage(int category);

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

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string SPO2::getMessage(int category) const {
    return getSPO2CategoryMessage(category);
}
