#include "./vitalBaseline.h"

VitalBaseline::VitalBaseline(float lowLimit, float highLimit,
    float toleranceLimit) :
    low(lowLimit), high(highLimit),
    tolerance(toleranceLimit) {
    initLevels();
}

void VitalBaseline::initLevels() {
    // Keep levels in sorted order
    // Level creation strategy can be changed in derived classes.
    levels.push_back(low);
    levels.push_back(low + (tolerance * high) / 100);
    levels.push_back(high - (tolerance * high) / 100);
    levels.push_back(high);
}
