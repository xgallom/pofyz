//
// Created by Milan Gallo on 25/03/2020.
//

#include "parameterTables.h"

const char *ParametersTable[PARAMETER_COUNT] = {
#define DEF(param) [PARAMETER_##param] = #param
		// SIMULATION PARAMETERS
		DEF(x_0),
		DEF(v_0),
		DEF(dt),

		// OBJECT PARAMETERS
		DEF(m),
		DEF(S),
		DEF(C),
		DEF(T)
#undef DEF
};

const char *ParametersDetailsTable[PARAMETER_COUNT][PARAMETERS_DETAILS_COUNT] = {
#define DEF(param, unit, desc) [PARAMETER_##param] = {unit, desc}
		// SIMULATION PARAMETERS
		DEF(x_0, "m"  , "Initial height of fall (positive upwards)"),
		DEF(v_0, "m/s", "Initial fall velocity  (positive upwards)"),
		DEF(dt , "s"  , "Time step of simulation"),

		// OBJECT PARAMETERS
		DEF(m  , "kg" , "Mass of falling object"),
		DEF(S  , "m2" , "Effective area of falling object"),
		DEF(C  , NULL , "Drag coefficient"),
		DEF(T  , "K"  , "Temperature of air")
#undef DEF
};
