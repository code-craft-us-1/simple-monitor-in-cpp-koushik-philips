#pragma once
#include "vital.h"

struct Temperature : public Vital
{
private:
    enum class Category {
        HYPOTHERMIA,
        NEAR_HYPO,
        NORMAL,
        NEAR_HYPER,
        HYPERTHERMIA
    };
    std::string measurementUnits;
public:
    Temperature(float temperature, std::string units = "Fahrenheit");
    void normalizeMeasurement();
    std::set<int> collectInvalidCategories() const override;
    std::string getMessage(int category) const override;
};