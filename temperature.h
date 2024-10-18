#pragma once
#include <set>
#include <string>
#include "./vital.h"

VitalBaseline& createTemperatureBaseline(float lowLimit, float highLimit,
                                         float toleranceLimit);

struct Temperature : public Vital {
 private:
  std::string measurementUnits;
  void normalizeMeasurement();
 public:
  explicit Temperature(float temperature, std::string units = "Fahrenheit");
  std::string getMessage(int category) const override;
  friend std::string getTemperatureCategoryMessage(int category);
};


