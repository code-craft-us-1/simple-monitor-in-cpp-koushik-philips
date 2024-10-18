#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "./vital.h"

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

VitalBaseline::VitalBaseline(float lowLimit, float highLimit,
    float toleranceLimit) :
    low(lowLimit), high(highLimit),
    tolerance(toleranceLimit) {
    initLevels();
}
void VitalBaseline::initLevels() {
    // Keep levels in sorted order
    levels.push_back(low);
    levels.push_back(low + (tolerance * high) / 100);
    levels.push_back(high - (tolerance * high) / 100);
    levels.push_back(high);
}

Vital::Vital(float vitalValue,const VitalBaseline& baseline) :
    value(vitalValue), vitalbase(baseline) {
}

std::set<int>& Vital::collectInvalidCategories() const {
    static auto numCategories{ static_cast<int>(vitalbase.levels.size()) };
    static std::set<int> invalidCategoies{ 0, 1, numCategories - 1, numCategories };
    return invalidCategoies;
}

int Vital::getCategory() const {
    auto iter = std::lower_bound(vitalbase.levels.begin(), vitalbase.levels.end(), value);
    if (value == vitalbase.low) {
        return static_cast<int>(std::distance(vitalbase.levels.begin(), iter)) + 1;
    } else {
        return static_cast<int>(std::distance(vitalbase.levels.begin(), iter));
    }
}

void Vital::displayMessage(std::string message) const {
    cout << message;
}

void Vital::displayTransitionGraphics() const {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool Vital::isVitalOk(int category) const {
    auto& invalidCategories = collectInvalidCategories();
    if (invalidCategories.find(category) != invalidCategories.end()) {
        return false;
    } else {
        return true;
    }
}
