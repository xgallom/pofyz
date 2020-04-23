//
// Created by xgallom on 4/23/20.
//

#include "dynamics.h"
#include "../data/temperature.h"
#include "../constants.h"
#include "../solvers/integrateRiemannSum.h"

static double reciprocalTemperatureFor(double x)
{
	return 1. / temperatureFor(x);
}

static double ro(double x)
{
	const double
			T = temperatureFor(x),
			MR = M / R,

			constant = p_0 * MR / T,
			exponential = exp(-g * MR * solveIntegrateRiemannSum(&reciprocalTemperatureFor, 0, x, 2048));

	return constant * exponential;
}

double K(double x)
{
	return 0.5 * C * S * ro(x) / m;
}
