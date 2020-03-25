//
// Created by xgallom on 3/25/20.
//

#include "general.h"

#define CELSIUS_KELVIN_OFFSET 273.15

double celsiusToKelvin(double t) { return t + CELSIUS_KELVIN_OFFSET; }
double kelvinToCelsius(double T) { return T - CELSIUS_KELVIN_OFFSET; }
