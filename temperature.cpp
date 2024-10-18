#include <set>
#include <string>
#include "./temperature.h"

using VitalConstants::TEMP_LIMIT_LOW;
using VitalConstants::TEMP_LIMIT_HIGH;
using VitalConstants::TOLERANCE_PERCENT;
extern std::string getTemperatureCategoryMessage(int category);

//  Singleton
VitalBaseline& createTemperatureBaseline(float lowLimit, float highLimit,
                                         float toleranceLimit) {
    static VitalBaseline temperatureBaseline(lowLimit, highLimit,
                                         toleranceLimit);
    return temperatureBaseline;
}

Temperature::Temperature(float temperature, std::string units) :
    Vital(temperature,
        createTemperatureBaseline(TEMP_LIMIT_LOW, TEMP_LIMIT_HIGH, TOLERANCE_PERCENT)),
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
