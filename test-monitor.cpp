#include "./monitor.h"
#include "gtest/gtest.h"

// Temperature ranges = {95,96.53,100.47,102}
// Pulse-rate ranges = {60, 61.5, 98.5, 100}
// SpO2 ranges = {90, 91.5,98.5,100}

TEST(Monitor, MonitorTemperature) {
    // Individual checks and boundary-conditions
    ASSERT_FALSE(CheckTemperatureVital(94));                    // Hypothermia
    ASSERT_FALSE(CheckTemperatureVital(95.0f));                 // Near Hpothermia
    ASSERT_FALSE(CheckTemperatureVital(96.53f));                // Near Hpothermia
    ASSERT_TRUE(CheckTemperatureVital(96.54f));                 // Normal
    ASSERT_TRUE(CheckTemperatureVital(100.47f));                // Normal
    ASSERT_FALSE(CheckTemperatureVital(100.48f));               // Near Hyperthermia
    ASSERT_FALSE(CheckTemperatureVital(102.0f));                // Near Hyperthermia
    ASSERT_FALSE(CheckTemperatureVital(103.5f));                // Hyperthermia
    ASSERT_TRUE(CheckTemperatureVital(37.f,"Celsius"));         // Normal
    ASSERT_TRUE(CheckTemperatureVital(98.6f, "Fahrenheit"));    // Normal
}
TEST(Monitor, MonitorPulseRate) {
    // Individual checks and boundary-conditions
    ASSERT_FALSE(CheckPulseRateVital(59));                  // Bradycardia
    ASSERT_FALSE(CheckPulseRateVital(60));                  // Near Bradycardia
    ASSERT_FALSE(CheckPulseRateVital(61.5f));               // Near Bradycardia
    ASSERT_TRUE(CheckPulseRateVital(61.54f));               // Normal
    ASSERT_TRUE(CheckPulseRateVital(98.5f));                // Normal
    ASSERT_FALSE(CheckPulseRateVital(98.6f));               // Near Tachycardia
    ASSERT_FALSE(CheckPulseRateVital(100));                 // Near Tachycardia
    ASSERT_FALSE(CheckPulseRateVital(101));                 // Tachycardia
}
TEST(Monitor, MonitorSpo2) {
    // Individual checks and boundary-conditions
    ASSERT_FALSE(CheckSPO2Vital(89));                       // Hypoaxemia
    ASSERT_FALSE(CheckSPO2Vital(90));                       // Near Hypoaxemia
    ASSERT_FALSE(CheckSPO2Vital(91.5f));                    // Near Hypoaxemia
    ASSERT_TRUE(CheckSPO2Vital(91.6f));                     // Normal
    ASSERT_TRUE(CheckSPO2Vital(98.5f));                     // Normal
    ASSERT_FALSE(CheckSPO2Vital(98.6f));                    // Near Hyperoaxemia
    ASSERT_FALSE(CheckSPO2Vital(100));                      // Near Hyperoaxemia
    ASSERT_FALSE(CheckSPO2Vital(101));                      // Hyperoaxemia
}
TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  // check combinations
  ASSERT_FALSE(vitalsOk(99, 102, 70));      //  not-OK- 1 (T,P-out,S-out)
  ASSERT_FALSE(vitalsOk(103, 80, 94));      //  not-OK- 2 (T-out,P,S)
  ASSERT_FALSE(vitalsOk(98, 105, 94));      //  not-OK- 3 (T,P-out,S)
  ASSERT_FALSE(vitalsOk(98, 80, 70));       //  not-OK- 4 (T,P,S-out)
  ASSERT_FALSE(vitalsOk(103, 105, 94));     //  not-OK- 5 (T-out,P-out,S)
  ASSERT_FALSE(vitalsOk(103, 80, 70));      //  not-OK- 6 (T-out,P,S-out)
  ASSERT_FALSE(vitalsOk(98, 105, 70));      //  not-OK- 7 (T,P-out,S-out)
  ASSERT_FALSE(vitalsOk(103, 105, 70));     //  not-OK- 8 (T-out,P-out,S-out)
  ASSERT_TRUE(vitalsOk(98.1f, 70, 98));     //  OK    - 9 (T,P,S)
}
