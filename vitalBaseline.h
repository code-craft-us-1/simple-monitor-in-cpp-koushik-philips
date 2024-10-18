#pragma once
#include <vector>
#include "./constants.h"

using VitalConstants::VITALS_MIN;
using VitalConstants::VITALS_MAX;
using VitalConstants::TOLERANCE_PERCENT;
using Levels = std::vector<float>;

struct VitalBaseline {
    const float low{ VITALS_MIN };
    const float high{ VITALS_MAX };
    const float tolerance{ TOLERANCE_PERCENT };
    Levels levels;

    VitalBaseline(float lowLimit, float highLimit,
        float toleranceLimit);
    void initLevels();
};