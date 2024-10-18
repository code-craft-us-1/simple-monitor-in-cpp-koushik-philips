#pragma once
#include <set>
#include <string>
#include "./vital.h"

struct Temperature : public Vital {
 private:
  enum class Category {
     HYPOTHERMIA,
     NEAR_HYPO,
     NORMAL,
     NEAR_HYPER,
     HYPERTHERMIA
  };
  std::string measurementUnits;
 public:
  explicit Temperature(float temperature, std::string units = "Fahrenheit");
  void normalizeMeasurement();
  std::set<int> collectInvalidCategories() const override;
  std::string getMessage(int category) const override;
  friend std::string getTemperatureCategoryMessage(int category);
};
