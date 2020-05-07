//
// Created by xgallom on 3/12/20.
//

#include "euler.h"
#include "solveGeneric.h"
#include "../../constants.h"
#include "../../equations/simulation/acceleration.h"

static void iterateEuler(double *restrict x, double *restrict v, size_t length, struct AccelerationData *restrict data)
{
	for(int i = 1; i < length; ++i) {
		const double a = acceleration(x[i - 1], v[i - 1], data);

		v[i] = v[i - 1] + a * dt;
		x[i] = x[i - 1] + v[i] * dt;
	}
}

size_t solveEuler(struct Vector *restrict x, struct Vector *restrict v)
{
	return solveGeneric(iterateEuler, x, v);
}
