//
// Created by xgallom on 4/23/20.
//

#include "dynamics.h"
#include "../../constants.h"
#include "../../data/temperature.h"

static inline double ro(double x, double integralT)
{
	const double
			T = temperatureFor(x),
			MR = M / R,

			constant = p_0 * MR / T,
			exponential = exp(-g * MR * integralT);


	return constant * exponential;
}

static inline double S(double deltaModifier)
{
	return S_0 + S_delta / deltaModifier;
}

static inline double C(double deltaModifier)
{
	return C_0 + C_delta / deltaModifier;
}

double K(double x, double integralT)
{
	const double deltaModifier = 1.0 + exp((x_delta + x) / x_max);
	return 0.5 * C(deltaModifier) * S(deltaModifier) * ro(x, integralT) / m;
}
