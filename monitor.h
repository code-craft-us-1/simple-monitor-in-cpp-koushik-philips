#pragma once
#include "vital.h"
#include "temperature.h"
#include "pulserate.h"
#include "spo2.h"

bool vitalsOk(float temperature, float pulseRate, float spo2);
bool vitalsOk(Temperature temperature, PulseRate pulseRate, SPO2 spo2);
bool vitalsOk(std::vector<Vital> vitals);
bool CheckTemperatureVital(float temperature, std::string units="Fahrenheit");
bool CheckPulseRateVital(float pulseRate);
bool CheckSPO2Vital(float spo2);
bool checkVital(const Vital& vital);