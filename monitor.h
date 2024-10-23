#pragma once
#include <string>
#include <memory>
#include "./vital.h"
#include "./temperature.h"
#include "./pulserate.h"
#include "./spo2.h"

bool vitalsOk(float temperature, float pulseRate, float spo2);
bool vitalsOk(Temperature temperature, PulseRate pulseRate, SPO2 spo2);
bool vitalsOk(std::vector< std::shared_ptr<Vital> > vitals);
bool isVitalNormal(std::shared_ptr<Vital> spVital);
bool isTemperatureNormal(float temperature, std::string units = "Fahrenheit");
bool isPulseRateNormal(float pulseRate);
bool isSPO2Normal(float spo2);
bool isVitalNormal(const Vital& vital);
