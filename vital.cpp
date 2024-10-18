#include <iostream>
#include <thread>
#include <chrono>
#include "./vital.h"

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

Vital::Vital(float lowLimit, float highLimit,
    float toleranceLimit, float vitalValue) :
    low(lowLimit), high(highLimit),
    tolerance(toleranceLimit), value(vitalValue) {}
void Vital::initLevels() {
    // Keep levels in sorted order
    levels.push_back(low);
    levels.push_back(low + (tolerance * high) / 100);
    levels.push_back(high - (tolerance * high) / 100);
    levels.push_back(high);
}
int Vital::getCategory() const {
    auto iter = std::lower_bound(levels.begin(), levels.end(), value);
    if (value == low) {
        return static_cast<int>(std::distance(levels.begin(), iter)) + 1;
    }
    else {
        return static_cast<int>(std::distance(levels.begin(), iter));
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
    auto invalidCategories = collectInvalidCategories();
    if (invalidCategories.find(category) != invalidCategories.end()) {
        return false;
    }
    else {
        return true;
    }
}
