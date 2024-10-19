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
    HYPERTHERMIA
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
  std::string getMessage(int category) const override;
  friend std::string getTemperatureCategoryMessage(int category);
};


