#include <memory>
#include "./monitor.h"
#include "gtest/gtest.h"
#include "./localization.h"

// Temperature ranges = {95,96.53,100.47,102}
// Pulse-rate ranges = {60, 61.5, 98.5, 100}
// SpO2 ranges = {90, 91.5,98.5,100}

Language  chosenLanguage(LANG::NONE);

TEST(Monitor, MonitorTemperature) {
    chosenLanguage.setLanguage(LANG::GERMAN);
    // Individual checks and boundary-conditions
    ASSERT_FALSE(isTemperatureNormal(94));                    // Hypothermia
    ASSERT_FALSE(isTemperatureNormal(95.0f));                 // Near Hpothermia
    ASSERT_FALSE(isTemperatureNormal(96.53f));                // Near Hpothermia
    ASSERT_TRUE(isTemperatureNormal(96.54f));                 // Normal
    ASSERT_TRUE(isTemperatureNormal(100.47f));                // Normal
    ASSERT_FALSE(isTemperatureNormal(100.48f));               // Near Hyperthermia
    ASSERT_FALSE(isTemperatureNormal(102.0f));                // Near Hyperthermia
    ASSERT_FALSE(isTemperatureNormal(103.5f));                // Hyperthermia
    ASSERT_TRUE(isTemperatureNormal(37.f, "Celsius"));        // Normal. Units mentioned.
    ASSERT_TRUE(isTemperatureNormal(98.6f, "Fahrenheit"));    // Normal. Units mentioned.
}

TEST(Monitor, MonitorPulseRate) {
    chosenLanguage.setLanguage(LANG::ENGLISH);
    // Individual checks and boundary-conditions
    ASSERT_FALSE(isPulseRateNormal(59));                  // Bradycardia
    ASSERT_FALSE(isPulseRateNormal(60));                  // Near Bradycardia
    ASSERT_FALSE(isPulseRateNormal(61.5f));               // Near Bradycardia
    ASSERT_TRUE(isPulseRateNormal(61.56f));               // Normal
    ASSERT_TRUE(isPulseRateNormal(98.5f));                // Normal
    ASSERT_FALSE(isPulseRateNormal(98.6f));               // Near Tachycardia
    ASSERT_FALSE(isPulseRateNormal(100));                 // Near Tachycardia
    ASSERT_FALSE(isPulseRateNormal(101));                 // Tachycardia
}

TEST(Monitor, MonitorSpo2) {
    chosenLanguage.setLanguage(LANG::GERMAN);
    // Individual checks and boundary-conditions
    ASSERT_FALSE(isSPO2Normal(89));                       // Hypoaxemia
    ASSERT_FALSE(isSPO2Normal(90));                       // Near Hypoaxemia
    ASSERT_FALSE(isSPO2Normal(91.5f));                    // Near Hypoaxemia
    ASSERT_TRUE(isSPO2Normal(91.6f));                     // Normal
    ASSERT_TRUE(isSPO2Normal(98.5f));                     // Normal
    ASSERT_FALSE(isSPO2Normal(98.6f));                    // Near Hyperoaxemia
    ASSERT_FALSE(isSPO2Normal(100));                      // Near Hyperoaxemia
    ASSERT_FALSE(isSPO2Normal(101));                      // Hyperoaxemia
}

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  chosenLanguage.setLanguage(LANG::ENGLISH);
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

TEST(Monitor, MonitorAllPossibleVitalCombos) {
    //  Different combination of vitals
    ASSERT_TRUE(vitalsOk({ std::make_shared<Temperature>(96.54f),
                           std::make_shared<PulseRate>(61.56f),
                           std::make_shared<SPO2>(91.6f) }));
    ASSERT_TRUE(vitalsOk({ std::make_shared<Temperature>(100.47f),
                           std::make_shared<PulseRate>(98.5f) }));
    ASSERT_TRUE(vitalsOk({ std::make_shared <PulseRate>(98.5f),
                           std::make_shared <SPO2>(91.6f) }));
    ASSERT_TRUE(vitalsOk({ std::make_shared <Temperature>(36.5f, "Celsius"),
                           std::make_shared <SPO2>(91.6f)}));
}

TEST(Monitor, TemperatureWithUnits) {
    ASSERT_TRUE(isTemperatureNormal(37.f, "Celsius"));
    ASSERT_TRUE(vitalsOk({ std::make_shared <Temperature>(37.f, "Celsius"),
                           std::make_shared <SPO2>(94.5f) }));
}

TEST(Monitor, DisplayMessageInGerman) {
    chosenLanguage.setLanguage(LANG::GERMAN);
    ASSERT_TRUE(vitalsOk(98.6f, 80, 97));
}

TEST(Monitor, DisplayMessageInEnglish) {
    chosenLanguage.setLanguage(LANG::ENGLISH);
    ASSERT_TRUE(vitalsOk(98.5f, 82, 97));
}

TEST(Monitor, DisplayMessageInLanguage_chosenFromConfig) {
    chosenLanguage.setLanguage(LANG::NONE);
    ASSERT_TRUE(vitalsOk(97.5f, 70, 96));
}

TEST(Monitor, UseBoundaryConstantsToCheck) {
    using TEMPERATURE_CONSTANTS::TEMP_LIMIT_HIGH;
    using TEMPERATURE_CONSTANTS::TEMP_LIMIT_LOW;
    using TEMPERATURE_CONSTANTS::TEMP_TOLERANCE_PERCENT;
    using PULSERATE_CONSTANTS::PULSE_LIMIT_LOW;
    using PULSERATE_CONSTANTS::PULSE_LIMIT_HIGH;
    using PULSERATE_CONSTANTS::PULSE_TOLERANCE_PERCENT;
    using SPO2_CONSTANTS::SPO2_LIMIT_LOW;
    using SPO2_CONSTANTS::SPO2_LIMIT_HIGH;
    using SPO2_CONSTANTS::SPO2_TOLERANCE_PERCENT;

    chosenLanguage.setLanguage(LANG::ENGLISH);
    ASSERT_TRUE(vitalsOk(TEMP_LIMIT_HIGH - 3, PULSE_LIMIT_HIGH - 3, SPO2_LIMIT_HIGH - 3));
    ASSERT_TRUE(vitalsOk(TEMP_LIMIT_LOW + 3, PULSE_LIMIT_LOW + 4, SPO2_LIMIT_LOW + 5));
}

