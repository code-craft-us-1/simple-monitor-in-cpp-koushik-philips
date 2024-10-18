#pragma once
#include <set>
#include <string>
#include "./vital.h"

VitalBaseline& createSPO2Baseline(float lowLimit, float highLimit,
                                  float toleranceLimit);

struct SPO2 : public Vital {
  explicit SPO2(float spo2);
  std::string getMessage(int category) const override;
  friend std::string getSPO2CategoryMessage(int category);
};
