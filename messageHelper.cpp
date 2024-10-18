//  Note: 'messageHelper.cpp' has CCN=6.
//  Hence, ignored to keep rest of the system conform to CCN=3

#include <string>
#include "./constants.h"
#include "./messageHelper.h"

using VitalConstants::TemperatureCategory;
using VitalConstants::PulseRateCategory;
using VitalConstants::SPO2Category;

std::string getTemperatureCategoryMessage(int category) {
  auto temperatureCategory = static_cast<TemperatureCategory>(category);
  switch (temperatureCategory) {
  case TemperatureCategory::HYPOTHERMIA:  return "Hypothermia : Temperature is critical!\n";
  case TemperatureCategory::NEAR_HYPO:    return "Warning: Approaching hypothermia\n";
  case TemperatureCategory::NORMAL:       return "Normal Temperature\n";
  case TemperatureCategory::NEAR_HYPER:   return "Warning: Approaching hyperthermia\n";
  case TemperatureCategory::HYPERTHERMIA: return "Hyperthermia : Temperature is critical!\n";
  default:
      break;
  }
  return "Error";
}

std::string getPulseRateCategoryMessage(int category) {
  auto pulseRateCategory = static_cast<PulseRateCategory>(category);
  switch (pulseRateCategory) {
  case PulseRateCategory::BRADYCARDIA: return "Bradycardia : Pulse Rate is out of range!\n";
  case PulseRateCategory::NEAR_BRADY:  return "Warning: Approaching bradycardia\n";
  case PulseRateCategory::NORMAL:      return "Normal pule rate\n";
  case PulseRateCategory::NEAR_TACHY:  return "Warning: Approaching tachycardia\n";
  case PulseRateCategory::TACHYCARDIA: return "Tachycardia : Pulse Rate is out of range!\n";
  default:
      break;
  }
    return "Error";
}

std::string getSPO2CategoryMessage(int category) {
  auto spo2category = static_cast<SPO2Category>(category);
  switch (spo2category) {
  case SPO2Category::HYPOAXEMIA:        return "Hypoaxemia : Oxygen Saturation out of range!\n";
  case SPO2Category::NEAR_HYPOAXEMIA:   return "Warning: Approaching hypoaxemia\n";
  case SPO2Category::NORMAL:            return "Normal oxygen saturation\n";
  case SPO2Category::NEAR_HYPEROAXEMIA: return "Warning: Approaching hyperoaxemia\n";
  case SPO2Category::HYPEROAXEMIA:      return "Hyperoaxemia : Oxygen Saturation out of range!\n";
  default:
      break;
  }
    return "Error";
}
