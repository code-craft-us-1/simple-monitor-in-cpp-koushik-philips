#include <string>
#include <utility>
#include "./localization.h"
#include "./pulserate.h"

extern Language chosenLanguage;

using PULSERATE_CONSTANTS::PULSE_LIMIT_LOW;
using PULSERATE_CONSTANTS::PULSE_LIMIT_HIGH;
using PULSERATE_CONSTANTS::PULSE_TOLERANCE_PERCENT;

PulseRate::PulseRate(float pulserate) :
    Vital(pulserate,
        createBaseline<PulseRateBaseline>(PULSE_LIMIT_LOW, PULSE_LIMIT_HIGH, TOLERANCE_PERCENT)) {
    initPulseRateMessageMap();
}

//  Moved code to 'messageHelper.cpp' for conforming to CCN=3
std::wstring PulseRate::getMessage(int category) const {
    auto& lookUpTable = chosenLanguage.getResourceTable();
    auto pulseRateCategory = static_cast<PulseRateCategory>(category);
    auto messageId = messageMap.at(pulseRateCategory);
    return lookUpTable[messageId];
}

void PulseRate::initPulseRateMessageMap() {
    messageMap.insert(std::make_pair(PulseRateCategory::BRADYCARDIA, L"PULSE_BRADYCARDIA"));
    messageMap.insert(std::make_pair(PulseRateCategory::NEAR_BRADY, L"PULSE_NEAR_BRADY"));
    messageMap.insert(std::make_pair(PulseRateCategory::NORMAL, L"PULSE_NORMAL"));
    messageMap.insert(std::make_pair(PulseRateCategory::NEAR_TACHY, L"PULSE_NEAR_TACHY"));
    messageMap.insert(std::make_pair(PulseRateCategory::TACHYCARDIA, L"PULSE_TACHYCARDIA"));
}
