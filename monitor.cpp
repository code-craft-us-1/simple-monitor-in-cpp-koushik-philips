#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

namespace {
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

bool CheckTemperatureVital(float temperature) {
    if (temperature > TEMP_LIMIT_HIGH || temperature < TEMP_LIMIT_LOW) {
        DisplayError("Temperature is critical!\n");
        return false;
    }
    return true;
}
bool CheckPulseRateVital(float pulseRate) {
    if (pulseRate < PULSE_LIMIT_LOW || pulseRate >PULSE_LIMIT_HIGH) {
        DisplayError("Pulse Rate is out of range!\n");
        return false;
    }
    return true;
}
bool CheckSPO2Vital(float spo2) {
    if (spo2 < SPO2_LIMIT_LOW) {
        DisplayError("Oxygen Saturation out of range!\n");
        return false;
    }
    return true;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (CheckTemperatureVital(temperature) &&
        CheckPulseRateVital(pulseRate) &&
        CheckSPO2Vital(spo2)) {
        return 1;
    }
    return 0;
}