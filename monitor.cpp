#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <limits>
#include <functional>
using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

namespace {
    constexpr float VITALS_MAX = std::numeric_limits<float>::max();
    constexpr float VITALS_MIN = std::numeric_limits<float>::min();
    constexpr int TEMP_LIMIT_HIGH = 102;
    constexpr int TEMP_LIMIT_LOW = 95;
    constexpr int PULSE_LIMIT_HIGH = 100;
    constexpr int PULSE_LIMIT_LOW = 60;
    constexpr int SPO2_LIMIT_LOW = 90;
}

void DisplayError(std::string error) {
    cout << error;
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}
enum class Operator {
    LT,
    LTEQ,
    GT,
    GTEQ
};
bool CompareFunc(float value, float limit, Operator type) {
    switch (type) {
    case (Operator::LT):
        return value < limit;
    case (Operator::GT):
        return value > limit;
    default:
        return false;
    }
}

using Func = std::function<bool(float, float, Operator)>;
bool CheckVital(float value, std::string msg,
                float low = VITALS_MIN, float high= VITALS_MAX,
                Func f = CompareFunc,
                Operator compareWithLow = Operator::LT,
                Operator compareWithHigh = Operator::GT) {
    if (f(value, low, compareWithLow) || f(value, high, compareWithHigh)) {
        DisplayError(msg);
        return false;
    }
    return true;
}

bool CheckTemperatureVital(float temperature) {
    return CheckVital(temperature, "Temperature is critical!\n",
                      TEMP_LIMIT_LOW, TEMP_LIMIT_HIGH);
}
bool CheckPulseRateVital(float pulseRate) {
    return CheckVital(pulseRate, "Pulse Rate is out of range!\n",
                      PULSE_LIMIT_LOW, PULSE_LIMIT_HIGH);
}
bool CheckSPO2Vital(float spo2) {
    return CheckVital(spo2, "Oxygen Saturation out of range!\n", SPO2_LIMIT_LOW);
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
    return CheckTemperatureVital(temperature) &&
           CheckPulseRateVital(pulseRate) &&
           CheckSPO2Vital(spo2);
}
