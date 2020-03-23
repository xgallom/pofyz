//
// Created by xgallom on 3/18/20.
//

#include "constants.h"

// SIMULATION PARAMETERS
double
		x_0 = 0.0,
		v_0 = 0.0,
		dt = 0.0;

// OBJECT PARAMETERS
double
		m = 0.0,
		S = 0.0,
		C = 0.0,
		T = 0.0;

// CALCULATED CONSTANT PARAMETERS
double
		ro_0 = 0.0,
		K_0 = 0.0,
		v_inf2 = 0.0,
		v_inf = 0.0,
		kappa = 0.0;

void initializeConstants(struct Arguments arguments)
{
	// SIMULATION PARAMETERS
	x_0 = arguments.parameters[PARAMETER_x_0];
	v_0 = arguments.parameters[PARAMETER_v_0];
	dt = arguments.parameters[PARAMETER_dt];

	// OBJECT PARAMETERS
	m = arguments.parameters[PARAMETER_m];
	S = arguments.parameters[PARAMETER_S];
	C = arguments.parameters[PARAMETER_C];
	T = arguments.parameters[PARAMETER_T];

	// CALCULATED CONSTANT PARAMETERS
	ro_0 = M * p_0 / (R * T);
	K_0 = 0.5 * C * S * ro_0 / m;
	v_inf2 = g / K_0;
	v_inf = sqrt(v_inf2);
	kappa = M * g / (R * T);
}
