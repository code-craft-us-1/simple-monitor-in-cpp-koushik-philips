#include "./monitor.h"
#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));      //  not-OK- 1
  ASSERT_FALSE(vitalsOk(103, 80, 94));      //  not-OK- 2
  ASSERT_FALSE(vitalsOk(98, 105, 94));      //  not-OK- 3
  ASSERT_FALSE(vitalsOk(98, 80, 70));       //  not-OK- 4
  ASSERT_FALSE(vitalsOk(103, 105, 94));     //  not-OK- 5
  ASSERT_FALSE(vitalsOk(103, 80, 70));      //  not-OK- 6
  ASSERT_FALSE(vitalsOk(98, 105, 70));      //  not-OK- 7
  ASSERT_FALSE(vitalsOk(103, 105, 70));     //  not-OK- 8
  ASSERT_TRUE(vitalsOk(98.1f, 70, 98));
}
