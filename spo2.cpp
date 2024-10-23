#include <string>
#include "./localization.h"
#include "./spo2.h"

extern Language chosenLanguage;

namespace {
constexpr float SPO2_LIMIT_LOW = 90;
constexpr float SPO2_LIMIT_HIGH = 100;
constexpr float SPO2_TOLERANCE_PERCENT = 1.5;
}

SPO2::SPO2(float spo2) :
    Vital(spo2,
        createBaseline<SPO2Baseline>(SPO2_LIMIT_LOW, SPO2_LIMIT_HIGH, TOLERANCE_PERCENT)) {
    initSPO2MessageMap();
}

std::wstring SPO2::getMessage(int category) const {
    auto& lookUpTable = chosenLanguage.getResourceTable();
    auto spo2Category = static_cast<SPO2Category>(category);
    auto messageId = messageMap.at(spo2Category);
    return lookUpTable[messageId];
}

void SPO2::initSPO2MessageMap() {
    messageMap.insert(std::make_pair(SPO2Category::HYPOAXEMIA, L"SPO2_HYPOAXEMIA"));
    messageMap.insert(std::make_pair(SPO2Category::NEAR_HYPOAXEMIA, L"SPO2_NEAR_HYPOAXEMIA"));
    messageMap.insert(std::make_pair(SPO2Category::NORMAL, L"SPO2_NORMAL"));
    messageMap.insert(std::make_pair(SPO2Category::NEAR_HYPEROAXEMIA, L"SPO2_NEAR_HYPEROAXEMIA"));
    messageMap.insert(std::make_pair(SPO2Category::HYPEROAXEMIA, L"SPO2_HYPEROAXEMIA"));
}
