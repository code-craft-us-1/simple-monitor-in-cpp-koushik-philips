#include <set>
#include <string>
#include "./temperature.h"

using VitalConstants::TEMP_LIMIT_LOW;
using VitalConstants::TEMP_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;

Temperature::Temperature(float temperature, std::string units) :
    Vital(TEMP_LIMIT_LOW, TEMP_LIMIT_HIGH,
        TOLERANCE_PERCENT, temperature),
    measurementUnits(units) {
    initLevels();
    normalizeMeasurement();
}
void Temperature::normalizeMeasurement() {
    if (measurementUnits == "Celsius") {
        value = ((9.0f / 5.0f) * value) + 32.0f;
    }
}
std::set<int> Temperature::collectInvalidCategories() const {
    std::set<int> invalidCategoies;
    invalidCategoies.insert(static_cast<int>(Category::HYPOTHERMIA));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_HYPO));
    invalidCategoies.insert(static_cast<int>(Category::NEAR_HYPER));
    invalidCategoies.insert(static_cast<int>(Category::HYPERTHERMIA));
    return invalidCategoies;
}
std::string Temperature::getMessage(int category) const {
    auto temperatureCategory = static_cast<Category>(category);
    switch (temperatureCategory) {
    case Category::HYPOTHERMIA:     return "Hypothermia : Temperature is critical!\n";
    case Category::NEAR_HYPO:       return "Warning: Approaching hypothermia\n";
    case Category::NORMAL:          return "Normal Temperature\n";
    case Category::NEAR_HYPER:      return "Warning: Approaching hyperthermia\n";
    case Category::HYPERTHERMIA:    return "Hyperthermia : Temperature is critical!\n";
    default:
        break;
    }
    return "Error";
}
