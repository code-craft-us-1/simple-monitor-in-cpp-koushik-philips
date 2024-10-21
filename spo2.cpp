#include <set>
#include <string>
#include "./spo2.h"

extern std::wstring getSPO2CategoryMessage(int category);

namespace {
constexpr float SPO2_LIMIT_LOW = 90;
constexpr float SPO2_LIMIT_HIGH = 100;
constexpr float SPO2_TOLERANCE_PERCENT = 1.5;
}

SPO2::SPO2(float spo2) :
    Vital(spo2,
        createBaseline<SPO2Baseline>(SPO2_LIMIT_LOW, SPO2_LIMIT_HIGH, TOLERANCE_PERCENT)) {
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::wstring SPO2::getMessage(int category) const {
    return getSPO2CategoryMessage(category);
}
