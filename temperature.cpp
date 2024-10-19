#include <set>
#include <string>
#include "./temperature.h"

extern std::string getTemperatureCategoryMessage(int category);

namespace {
constexpr float TEMP_LIMIT_HIGH = 102;
constexpr float TEMP_LIMIT_LOW = 95;
constexpr float TEMP_TOLERANCE_PERCENT = 1.5;
}

Temperature::Temperature(float temperature, std::string units) :
    Vital(temperature,
        createBaseline<TemperatureBaseline>(TEMP_LIMIT_LOW, TEMP_LIMIT_HIGH,
                                            TEMP_TOLERANCE_PERCENT)),
    measurementUnits(units) {
    normalizeMeasurement();
}

void Temperature::normalizeMeasurement() {
    if (measurementUnits == "Celsius") {
        value = ((9.0f / 5.0f) * value) + 32.0f;
    }
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::string Temperature::getMessage(int category) const {
    return getTemperatureCategoryMessage(category);
}
