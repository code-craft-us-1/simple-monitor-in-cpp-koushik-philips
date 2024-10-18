#pragma once
#include <string>
#include <vector>
#include <set>
#include "./constants.h"

using VitalConstants::VITALS_MIN;
using VitalConstants::VITALS_MAX;
using VitalConstants::TOLERANCE_PERCENT;
using Levels = std::vector<float>;

struct Vital {
    const float low{ VITALS_MIN };
    const float high{ VITALS_MAX };
    const float tolerance{ TOLERANCE_PERCENT };
    float value;
    Levels levels;

    Vital(float lowLimit, float highLimit,
        float toleranceLimit, float vitalValue);
    virtual ~Vital() = default;
    virtual std::set<int> collectInvalidCategories() const = 0;
    virtual std::string getMessage(int category) const = 0;
    void initLevels();
    int  getCategory() const;
    void displayMessage(std::string message) const;
    void displayTransitionGraphics() const;
    bool isVitalOk(int category) const;
};
