#pragma once
#include <set>
#include <string>
#include "./vital.h"

// Number of categories = number of 'levels' + 1
enum class SPO2Category {
    HYPOAXEMIA,
    NEAR_HYPOAXEMIA,
    NORMAL,
    NEAR_HYPEROAXEMIA,
    HYPEROAXEMIA,
    COUNT_MAX
};

struct SPO2Baseline : public VitalBaseline {
    SPO2Baseline(float lowLimit, float highLimit,
        float toleranceLimit) :
        VitalBaseline(lowLimit, highLimit, toleranceLimit) {
    }
};

struct SPO2 : public Vital {
  explicit SPO2(float spo2);
  std::wstring getMessage(int category) const override;
  friend std::wstring getSPO2CategoryMessage(int category);
};
