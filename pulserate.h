#pragma once
#include <set>
#include <string>
#include "./vital.h"

VitalBaseline& createPulseRateBaseline(float lowLimit, float highLimit,
                                       float toleranceLimit);

struct PulseRate : public Vital {
  explicit PulseRate(float pulserate);
  std::string getMessage(int category) const override;
  friend std::string getPulseRateCategoryMessage(int category);
};
