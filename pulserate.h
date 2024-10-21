#pragma once
#include <set>
#include <string>
#include "./vital.h"

// Number of categories = number of 'levels' + 1
enum class PulseRateCategory {
    BRADYCARDIA,
    NEAR_BRADY,
    NORMAL,
    NEAR_TACHY,
    TACHYCARDIA,
    COUNT_MAX
};

struct PulseRateBaseline : public VitalBaseline {
    PulseRateBaseline(float lowLimit, float highLimit,
        float toleranceLimit) :
        VitalBaseline(lowLimit, highLimit, toleranceLimit) {
    }
};

struct PulseRate : public Vital {
  explicit PulseRate(float pulserate);
  std::wstring getMessage(int category) const override;
  friend std::wstring getPulseRateCategoryMessage(int category);
};
