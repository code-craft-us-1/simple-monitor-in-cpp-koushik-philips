#pragma once
#include <string>
#include <map>
#include "./vital.h"

namespace PULSERATE_CONSTANTS {
    constexpr float PULSE_LIMIT_HIGH = 100;
    constexpr float PULSE_LIMIT_LOW = 60;
    constexpr float PULSE_TOLERANCE_PERCENT = 1.5;
}
using MessageID = std::wstring;

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
 private:
  std::map<PulseRateCategory, MessageID> messageMap;
  void initPulseRateMessageMap();
 public:
  explicit PulseRate(float pulserate);
  std::wstring getMessage(int category) const override;
};
