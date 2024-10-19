#pragma once
#include <vector>
#include <limits>

namespace VitalConstants {
constexpr float VITALS_MAX = std::numeric_limits<float>::max();
constexpr float VITALS_MIN = std::numeric_limits<float>::min();
constexpr float TOLERANCE_PERCENT = 1.5;
}

using VitalConstants::VITALS_MAX;
using VitalConstants::VITALS_MIN;
using VitalConstants::TOLERANCE_PERCENT;
using Levels = std::vector<float>;

struct VitalBaseline {
    const float low{ VITALS_MIN };
    const float high{ VITALS_MAX };
    const float tolerance{ TOLERANCE_PERCENT };
    Levels levels;

    VitalBaseline(float lowLimit, float highLimit,
        float toleranceLimit);
    virtual ~VitalBaseline() = default;
    virtual void initLevels();
};

//  singleton
template<typename T>
T& createBaseline(float lowLimit, float highLimit,
    float toleranceLimit) {
    static T baseline(lowLimit, highLimit,
                                 toleranceLimit);
    return baseline;
}
