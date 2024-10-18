#include "./monitor.h"
#include <memory>
#include <string>

//  Template
bool checkVital(const Vital& vital) {
    auto category = vital.getCategory();
    auto msg = vital.getMessage(category);
    vital.displayMessage(msg);
    vital.displayTransitionGraphics();
    return vital.isVitalOk(category);
}

//  Template
bool checkVital(std::shared_ptr<Vital> spVital) {
    auto category = spVital->getCategory();
    auto msg = spVital->getMessage(category);
    spVital->displayMessage(msg);
    spVital->displayTransitionGraphics();
    return spVital->isVitalOk(category);
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

// overload
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    return CheckTemperatureVital(temperature) &&
           CheckPulseRateVital(pulseRate) &&
           CheckSPO2Vital(spo2);
}

// overload
bool vitalsOk(Temperature temperature, PulseRate pulseRate, SPO2 spo2) {
    return checkVital(temperature) &&
           checkVital(pulseRate) &&
           checkVital(spo2);
}

// overload
bool vitalsOk(std::vector< std::shared_ptr<Vital> > vitals) {
    bool ret = true;
    for ( auto item : vitals ) {
        ret = (ret && checkVital(item) );
    }
    return ret;
}
