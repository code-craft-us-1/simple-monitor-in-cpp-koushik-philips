#include "./monitor.h"
#include <string>

// Template design pattern
bool checkVital(const Vital& vital) {
    auto category = vital.getCategory();
    auto msg = vital.getMessage(category);
    vital.displayMessage(msg);
    vital.displayTransitionGraphics();
    return vital.isVitalOk(category);
}

bool CheckTemperatureVital(float temperature, std::string units) {
    return checkVital(Temperature(temperature, units));
}

bool CheckPulseRateVital(float pulseRate) {
    return checkVital(PulseRate(pulseRate));
}

bool CheckSPO2Vital(float spo2) {
    return checkVital(SPO2(spo2));
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
    return CheckTemperatureVital(temperature) &&
           CheckPulseRateVital(pulseRate) &&
           CheckSPO2Vital(spo2);
}

bool vitalsOk(Temperature temperature, PulseRate pulseRate, SPO2 spo2) {
    return checkVital(temperature) &&
           checkVital(pulseRate) &&
           checkVital(spo2);
}

bool vitalsOk(std::vector<Vital> vitals) {
    bool ret = true;
    for ( auto& item : vitals ) {
        ret = (ret && checkVital(item) );
    }
    return ret;
}
