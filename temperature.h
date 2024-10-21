#pragma once
#include <set>
#include <string>
#include "./vital.h"

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
  std::string measurementUnits;
  void normalizeMeasurement();
 public:
  explicit Temperature(float temperature, std::string units = "Fahrenheit");
  std::wstring getMessage(int category) const override;
  friend std::wstring getTemperatureCategoryMessage(int category);
};


