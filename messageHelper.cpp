//  Note: 'messageHelper.cpp' has CCN=6.
//  Hence, ignored to keep rest of the system conform to CCN=3

#include <string>
#include "./messageHelper.h"
#include "./temperature.h"
#include "./pulserate.h"
#include "./spo2.h"
#include "./localization.h"

std::wstring getTemperatureCategoryMessage(int category) {
  auto& lookUpTable = Language::getResourceTable();
  auto temperatureCategory = static_cast<TemperatureCategory>(category);
  switch (temperatureCategory) {
  case TemperatureCategory::HYPOTHERMIA:  return lookUpTable[L"TEMP_HYPOTHERMIA"];
  case TemperatureCategory::NEAR_HYPO:    return lookUpTable[L"TEMP_NEAR_HYPO"];
  case TemperatureCategory::NORMAL:       return lookUpTable[L"TEMP_NORMAL"];
  case TemperatureCategory::NEAR_HYPER:   return lookUpTable[L"TEMP_NEAR_HYPER"];
  case TemperatureCategory::HYPERTHERMIA: return lookUpTable[L"TEMP_HYPERTHERMIA"];
  default:
      break;
  }
  return std::wstring(L"Error");
}


std::wstring getPulseRateCategoryMessage(int category) {
  auto& lookUpTable = Language::getResourceTable();
  auto pulseRateCategory = static_cast<PulseRateCategory>(category);
  switch (pulseRateCategory) {
  case PulseRateCategory::BRADYCARDIA: return lookUpTable[L"PULSE_BRADYCARDIA"];
  case PulseRateCategory::NEAR_BRADY:  return lookUpTable[L"PULSE_NEAR_BRADY"];
  case PulseRateCategory::NORMAL:      return lookUpTable[L"PULSE_NORMAL"];
  case PulseRateCategory::NEAR_TACHY:  return lookUpTable[L"PULSE_NEAR_TACHY"];
  case PulseRateCategory::TACHYCARDIA: return lookUpTable[L"PULSE_TACHYCARDIA"];
  default:
      break;
  }
    return std::wstring(L"Error");
}

std::wstring getSPO2CategoryMessage(int category) {
  auto& lookUpTable = Language::getResourceTable();
  auto spo2category = static_cast<SPO2Category>(category);
  switch (spo2category) {
  case SPO2Category::HYPOAXEMIA:        return lookUpTable[L"SPO2_HYPOAXEMIA"];
  case SPO2Category::NEAR_HYPOAXEMIA:   return lookUpTable[L"SPO2_NEAR_HYPOAXEMIA"];
  case SPO2Category::NORMAL:            return lookUpTable[L"SPO2_NORMAL"];
  case SPO2Category::NEAR_HYPEROAXEMIA: return lookUpTable[L"SPO2_NEAR_HYPEROAXEMIA"];
  case SPO2Category::HYPEROAXEMIA:      return lookUpTable[L"SPO2_HYPEROAXEMIA"];
  default:
      break;
  }
    return std::wstring(L"Error");
}
