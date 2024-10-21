#include "./monitor.h"
#include <memory>
#include <string>

//  Template
bool isVitalNormal(const Vital& vital) {
    auto category = vital.getCategory();
    auto& msg = vital.getMessage(category);
    vital.displayMessage(msg);
    //vital.displayTransitionGraphics();
    return vital.isVitalOk(category);
}

//  Template
bool isVitalNormal(std::shared_ptr<Vital> spVital) {
    auto category = spVital->getCategory();
    auto msg = spVital->getMessage(category);
    spVital->displayMessage(msg);
    //spVital->displayTransitionGraphics();
    return spVital->isVitalOk(category);
}

bool isTemperatureNormal(float temperature, std::string units) {
    return isVitalNormal(Temperature(temperature, units));
}

bool isPulseRateNormal(float pulseRate) {
    return isVitalNormal(PulseRate(pulseRate));
}

bool isSPO2Normal(float spo2) {
    return isVitalNormal(SPO2(spo2));
}

// overload
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    return isTemperatureNormal(temperature) &&
           isPulseRateNormal(pulseRate) &&
           isSPO2Normal(spo2);
}

// overload
bool vitalsOk(Temperature temperature, PulseRate pulseRate, SPO2 spo2) {
    return isVitalNormal(temperature) &&
           isVitalNormal(pulseRate) &&
           isVitalNormal(spo2);
}

// overload
bool vitalsOk(std::vector< std::shared_ptr<Vital> > vitals) {
    bool ret = true;
    for ( auto item : vitals ) {
        ret = (ret && isVitalNormal(item) );
    }
    return ret;
}
