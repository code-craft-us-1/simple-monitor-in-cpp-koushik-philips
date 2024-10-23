#pragma once
#include <string>
#include <map>
#include "./vital.h"

namespace TEMPERATURE_CONSTANTS {
constexpr float TEMP_LIMIT_HIGH = 102;
constexpr float TEMP_LIMIT_LOW = 95;
constexpr float TEMP_TOLERANCE_PERCENT = 1.5;
}
using MessageID = std::wstring;

// Number of categories = number of 'levels' + 1
enum class TemperatureCategory {
    HYPOTHERMIA,
    NEAR_HYPO,
    NORMAL,
    NEAR_HYPER,
    HYPERTHERMIA,
    COUNT_MAX
};

struct TemperatureBaseline : public VitalBaseline {
    TemperatureBaseline(float lowLimit, float highLimit,
        float toleranceLimit) :
        VitalBaseline(lowLimit, highLimit, toleranceLimit) {
    }
};

struct Temperature : public Vital {
 private:
  std::map<TemperatureCategory, MessageID> messageMap;
  std::string measurementUnits;
  void normalizeMeasurement();
  void initTemperatureMessageMap();
 public:
  explicit Temperature(float temperature, std::string units = "Fahrenheit");
  std::wstring getMessage(int category) const override;
};


