//
// Created by xgallom on 3/18/20.
//

#include "constants.h"
#include "arguments/arguments.h"
#include "core/error.h"

// SIMULATION PARAMETERS
double
		x_0 = 0.0,
		v_0 = 0.0,
		dt = 0.0;

// OBJECT PARAMETERS
double
		m = 0.0,
		x_delta = 0.0,
		x_max = 0.0,
		S_0 = 0.0,
		S_delta = 0.0,
		C_0 = 0.0,
		C_delta = 0.0;

void initializeConstants(const struct Arguments *arguments)
{
	// SIMULATION PARAMETERS
	x_0 = arguments->parameter.x_0;
	v_0 = arguments->parameter.v_0;
	dt = arguments->parameter.dt;

	fail(x_0 < 0.0, "Invalid value of x_0: %.2f\n", x_0);

	// OBJECT PARAMETERS
	m = arguments->parameter.m;
	x_delta = arguments->parameter.x_open - x_0;
	x_max = arguments->parameter.x_max;
	S_0 = arguments->parameter.S_0;
	S_delta = arguments->parameter.S_max - S_0;
	C_0 = arguments->parameter.C_0;
	C_delta = arguments->parameter.C_max - C_0;
}
