#pragma once
#include <string>
#include <vector>
#include <set>
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

struct Vital {
    float value;
    const VitalBaseline& vitalbase;

    Vital(float vitalValue, const VitalBaseline& baseline);
    virtual ~Vital() = default;
    virtual std::set<int>& collectInvalidCategories() const;
    virtual std::string getMessage(int category) const = 0;
    int  getCategory() const;
    void displayMessage(std::string message) const;
    void displayTransitionGraphics() const;
    bool isVitalOk(int category) const;
};
