#pragma once
#include "vital.h"

struct PulseRate : public Vital
{
private:
    enum class Category {
        BRADYCARDIA,
        NEAR_BRADY,
        NORMAL,
        NEAR_TACHY,
        TACHYCARDIA
    };
public:
    PulseRate(float pulserate);
    std::set<int> collectInvalidCategories() const override;
    std::string getMessage(int category) const override;
};