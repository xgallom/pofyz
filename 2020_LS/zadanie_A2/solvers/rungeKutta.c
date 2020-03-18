//
// Created by xgallom on 3/12/20.
//

#include "rungeKutta.h"
#include "../constants.h"
#include "../equations/acceleration.h"
#include "../equations/velocity.h"

void solveRungeKutta(double *x, double *v)
{
	double
			x_i = x[0] = x_0,
			v_i = v[0] = v_0;

	for(int i = 1; i < steps; ++i) {
		const double
				v1 = dt * acceleration(x_i, v_i),
				x1 = dt * velocity(x_i, v_i),

				x2_i = x_i + x1 / 2.0, v2_i = v_i + v1 / 2.0,
				v2 = dt * acceleration(x2_i, v2_i),
				x2 = dt * velocity(x2_i, v2_i),

				x3_i = x_i + x2 / 2.0, v3_i = v_i + v2 / 2.0,
				v3 = dt * acceleration(x3_i, v3_i),
				x3 = dt * velocity(x3_i, v3_i),

				x4_i = x_i + x3, v4_i = v_i + v3,
				v4 = dt * acceleration(x4_i, v4_i),
				x4 = dt * velocity(x4_i, v4_i);

		x_i = x[i] = x_i + (x1 + 2.0 * x2 + 2.0 * x3 + x4) / 6.0;
		v_i = v[i] = v_i + (v1 + 2.0 * v2 + 2.0 * v3 + v4) / 6.0;
	}
}
