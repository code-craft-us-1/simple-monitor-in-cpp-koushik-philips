#include <string>
#include <utility>
#include "./localization.h"
#include "./temperature.h"

extern Language chosenLanguage;

using TEMPERATURE_CONSTANTS::TEMP_LIMIT_HIGH;
using TEMPERATURE_CONSTANTS::TEMP_LIMIT_LOW;
using TEMPERATURE_CONSTANTS::TEMP_TOLERANCE_PERCENT;

Temperature::Temperature(float temperature, std::string units) :
    Vital(temperature,
        createBaseline<TemperatureBaseline>(TEMP_LIMIT_LOW, TEMP_LIMIT_HIGH,
                                            TEMP_TOLERANCE_PERCENT)),
    measurementUnits(units) {
    normalizeMeasurement();
    initTemperatureMessageMap();
}

void Temperature::normalizeMeasurement() {
    if (measurementUnits == "Celsius") {
        value = ((9.0f / 5.0f) * value) + 32.0f;
    }
}

std::wstring Temperature::getMessage(int category) const {
    auto& lookUpTable = chosenLanguage.getResourceTable();
    auto temperatureCategory = static_cast<TemperatureCategory>(category);
    auto messageId = messageMap.at(temperatureCategory);
    return lookUpTable[messageId];
}

void Temperature::initTemperatureMessageMap() {
  messageMap.insert(std::make_pair(TemperatureCategory::HYPOTHERMIA, L"TEMP_HYPOTHERMIA"));
  messageMap.insert(std::make_pair(TemperatureCategory::NEAR_HYPO, L"TEMP_NEAR_HYPO"));
  messageMap.insert(std::make_pair(TemperatureCategory::NORMAL, L"TEMP_NORMAL"));
  messageMap.insert(std::make_pair(TemperatureCategory::NEAR_HYPER, L"TEMP_NEAR_HYPER"));
  messageMap.insert(std::make_pair(TemperatureCategory::HYPERTHERMIA, L"TEMP_HYPERTHERMIA"));
}
