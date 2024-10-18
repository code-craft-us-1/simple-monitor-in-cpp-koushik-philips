#pragma once
#include <string>
#include <vector>
#include <set>
#include "./constants.h"
#include "./vitalBaseline.h"

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
