//
// Created by xgallom on 4/23/20.
//

#include "dynamics.h"
#include "../data/temperature.h"
#include "../constants.h"

static double ro(double x, double integralT)
{
	const double
			T = temperatureFor(x),
			MR = M / R,

			constant = p_0 * MR / T,
			exponential = exp(-g * MR * integralT);


	return constant * exponential;
}

double K(double x, double integralT)
{
	return 0.5 * C * S * ro(x, integralT) / m;
}
