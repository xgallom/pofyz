//
// Created by xgallom on 3/12/20.
//

#include "analytical.h"
#include "constants.h"

void analytical(double *x, double *v)
{
	const double c_v_inf = v_inf();

	for(int i = 0; i < steps; ++i) {
		const double
				t = i * dt,
				angle = g * t / c_v_inf;

		x[i] = x_0 - v_inf2 * log(cosh(angle)) / g;
		v[i] = -c_v_inf * tanh(angle);
	}
}

double tD()
{
	return v_inf() * acosh(exp(g * x_0 / v_inf2)) / g;
}

double vD()
{
	return v_inf() * sqrt(1.0 - exp(-2.0 * g * x_0 / v_inf2));
}
