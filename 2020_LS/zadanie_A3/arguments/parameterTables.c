//
// Created by Milan Gallo on 25/03/2020.
//

#include "parameterTables.h"

#include <stddef.h>

const char *ParametersTable[PARAMETER_COUNT] = {
#define DEF(param) [PARAMETER_##param] = #param
		// SIMULATION PARAMETERS
		DEF(x_0),
		DEF(v_0),
		DEF(dt),

		// OBJECT PARAMETERS
		DEF(m),
		DEF(x_open),
		DEF(x_max),
		DEF(S_0),
		DEF(S_max),
		DEF(C_0),
		DEF(C_max),
#undef DEF
};

const char *ParametersDetailsTable[PARAMETER_COUNT][PARAMETERS_DETAILS_COUNT] = {
#define DEF(param, unit, desc) [PARAMETER_##param] = {unit, desc}
		// SIMULATION PARAMETERS
		DEF(x_0, "m", "Initial height of fall (positive upwards)"),
		DEF(v_0, "m/s", "Initial fall velocity  (positive upwards)"),
		DEF(dt, "s", "Time step of simulation"),

		// OBJECT PARAMETERS
		DEF(m, "kg", "Mass of falling object"),
		DEF(x_open, "m", "Distance travelled before opening parachute"),
		DEF(x_max, "m", "Distance travelled to fully open parachute"),
		DEF(S_0, "m2", "Starting effective area of parachute"),
		DEF(S_max, "m2", "Final effective area of parachute"),
		DEF(C_0, NULL, "Starting drag coefficient of parachute"),
		DEF(C_max, NULL, "Final drag coefficient of parachute"),
#undef DEF
};
