//
// Created by xgallom on 4/23/20.
//

#include "dynamics.h"
#include "../data/temperature.h"
#include "../constants.h"

double reciprocalTemperatureFor(double x)
{
	return 1. / temperatureFor(x);
}

static double ro(double x, double *oldX, double *oldIntegralT)
{
	const double delta = x - *oldX;
	*oldIntegralT += reciprocalTemperatureFor(*oldX + delta / 2.0) * delta;
	*oldX = x;

	const double
			T = temperatureFor(x),
			MR = M / R,

			constant = p_0 * MR / T,
			exponential = exp(-g * MR * *oldIntegralT);


	return constant * exponential;
}

double K(double x, double *oldX, double *oldIntegralT)
{
	return 0.5 * C * S * ro(x, oldX, oldIntegralT) / m;
}
