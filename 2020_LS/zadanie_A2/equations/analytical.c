//
// Created by xgallom on 3/12/20.
//

#include "analytical.h"
#include "../constants.h"
#include "../core/vector.h"

size_t analytical(struct Vector *x_vec, struct Vector *v_vec)
{
	const size_t length = ceil(tD() / dt);
	resize(x_vec, length);
	resize(v_vec, length);

	double
			*const x = asDouble(x_vec),
			*const v = asDouble(v_vec);

	for(int i = 0; i < length; ++i) {
		const double
				t = i * dt,
				angle = g * t / v_inf;

		x[i] = x_0 - v_inf2 * log(cosh(angle)) / g;
		v[i] = -v_inf * tanh(angle);
	}

	return length;
}

double tD()
{
	return v_inf * acosh(exp(g * x_0 / v_inf2)) / g;
}

double vD()
{
	return v_inf * sqrt(1.0 - exp(-2.0 * g * x_0 / v_inf2));
}
