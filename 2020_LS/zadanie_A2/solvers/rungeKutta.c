//
// Created by xgallom on 3/12/20.
//

#include "rungeKutta.h"
#include "../constants.h"
#include "../acceleration.h"

void solveRungeKutta(double *x, double *v)
{
	x[0] = x_0;
	v[0] = v_0;

	for(int i = 1; i < steps; ++i) {
		const double
				x_i = x[i - 1],
				v_i = v[i - 1],

				k1 = dt * acceleration(x_i, v_i),
				v1 = k1 / 2.0,

				k2 = dt * acceleration(x_i + v1 * dt, v_i + v1),
				v2 = k2 / 2.0,

				k3 = dt * acceleration(x_i + v2 * dt, v_i + v2),
				v3 = k3,

				k4 = dt * acceleration(x_i + v3 * dt, v_i + v3);

		v[i] = v_i + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
		x[i] = x_i + v[i] * dt;
	}
}
