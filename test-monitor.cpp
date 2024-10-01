#include "./monitor.h"
#include "gtest/gtest.h"

TEST(Monitor, IndividualVitalsOk) {
    // Individual checks and boundary-conditions
    ASSERT_FALSE(CheckTemperatureVital(94));        // Low Temp
    ASSERT_TRUE(CheckTemperatureVital(95.0f));      // Ok Temp
    ASSERT_TRUE(CheckTemperatureVital(102));        // Ok Temp
    ASSERT_FALSE(CheckTemperatureVital(103.5f));    // High Temp
    ASSERT_FALSE(CheckPulseRateVital(59));          // Low Pulse
    ASSERT_TRUE(CheckPulseRateVital(60));           // Ok Pulse
    ASSERT_TRUE(CheckPulseRateVital(100));          // Ok Pulse
    ASSERT_FALSE(CheckPulseRateVital(101));         // High Pulse
    ASSERT_FALSE(CheckSPO2Vital(89));               // Low SPO2
    ASSERT_TRUE(CheckSPO2Vital(90));                // Ok SPO2
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
