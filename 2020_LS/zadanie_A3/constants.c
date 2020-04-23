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
		S = 0.0,
		C = 0.0;

void initializeConstants(const struct Arguments *arguments)
{
	// SIMULATION PARAMETERS
	x_0 = arguments->parameter.x_0;
	v_0 = arguments->parameter.v_0;
	dt = arguments->parameter.dt;

	fail(x_0 < 0.0, "Invalid value of x_0: %.2f\n", x_0);

	// OBJECT PARAMETERS
	m = arguments->parameter.m;
	S = arguments->parameter.S;
	C = arguments->parameter.C;
}
