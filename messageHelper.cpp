//  Note: 'messageHelper.cpp' has CCN=6.
//  Hence, ignored to keep rest of the system conform to CCN=3

#include <string>
#include "./temperature.h"
#include "./pulserate.h"
#include "./spo2.h"
#include "./messageHelper.h"

std::string getTemperatureCategoryMessage(int category) {
  auto temperatureCategory = static_cast<Temperature::Category>(category);
  switch (temperatureCategory) {
  case Temperature::Category::HYPOTHERMIA:  return "Hypothermia : Temperature is critical!\n";
  case Temperature::Category::NEAR_HYPO:    return "Warning: Approaching hypothermia\n";
  case Temperature::Category::NORMAL:       return "Normal Temperature\n";
  case Temperature::Category::NEAR_HYPER:   return "Warning: Approaching hyperthermia\n";
  case Temperature::Category::HYPERTHERMIA: return "Hyperthermia : Temperature is critical!\n";
  default:
      break;
  }
  return "Error";
}

std::string getPulseRateCategoryMessage(int category) {
  auto pulseRateCategory = static_cast<PulseRate::Category>(category);
  switch (pulseRateCategory) {
  case PulseRate::Category::BRADYCARDIA: return "Bradycardia : Pulse Rate is out of range!\n";
  case PulseRate::Category::NEAR_BRADY:  return "Warning: Approaching bradycardia\n";
  case PulseRate::Category::NORMAL:      return "Normal pule rate\n";
  case PulseRate::Category::NEAR_TACHY:  return "Warning: Approaching tachycardia\n";
  case PulseRate::Category::TACHYCARDIA: return "Tachycardia : Pulse Rate is out of range!\n";
  default:
      break;
  }
    return "Error";
}

std::string getSPO2CategoryMessage(int category) {
  auto spo2category = static_cast<SPO2::Category>(category);
  switch (spo2category) {
  case SPO2::Category::HYPOAXEMIA:        return "Hypoaxemia : Oxygen Saturation out of range!\n";
  case SPO2::Category::NEAR_HYPOAXEMIA:   return "Warning: Approaching hypoaxemia\n";
  case SPO2::Category::NORMAL:            return "Normal oxygen saturation\n";
  case SPO2::Category::NEAR_HYPEROAXEMIA: return "Warning: Approaching hyperoaxemia\n";
  case SPO2::Category::HYPEROAXEMIA:      return "Hyperoaxemia : Oxygen Saturation out of range!\n";
  default:
      break;
  }
    return "Error";
}
