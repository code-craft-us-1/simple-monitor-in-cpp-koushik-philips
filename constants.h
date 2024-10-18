#pragma once
#include <limits>

namespace VitalConstants {
constexpr float VITALS_MAX = std::numeric_limits<float>::max();
constexpr float VITALS_MIN = std::numeric_limits<float>::min();
constexpr float TEMP_LIMIT_HIGH = 102;
constexpr float TEMP_LIMIT_LOW = 95;
constexpr float PULSE_LIMIT_HIGH = 100;
constexpr float PULSE_LIMIT_LOW = 60;
constexpr float SPO2_LIMIT_LOW = 90;
constexpr float SPO2_LIMIT_HIGH = 100;
constexpr float TOLERANCE_PERCENT = 1.5;
}  //  namespace VitalConstants
