//
// Created by xgallom on 3/12/20.
//

#include "euler.h"
#include "../constants.h"
#include "../acceleration.h"

void solveEuler(double *x, double *v)
{
	x[0] = x_0;
	v[0] = v_0;

	for(int i = 1; i < steps; ++i) {
		const double a = acceleration(x[i - 1], v[i - 1]);

		v[i] = v[i - 1] + a * dt;
		x[i] = x[i - 1] + v[i] * dt;
	}
}
