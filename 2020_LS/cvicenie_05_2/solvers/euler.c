//
// Created by xgallom on 3/12/20.
//

#include "euler.h"
#include "solveGeneric.h"
#include "../constants.h"
#include "../equations/acceleration.h"

static void iterateEuler(double *x, double *v, size_t length)
{
	for(int i = 1; i < length; ++i) {
		const double a = acceleration(x[i - 1], v[i - 1]);

		v[i] = v[i - 1] + a * dt;
		x[i] = x[i - 1] + v[i] * dt;
	}
}

size_t solveEuler(struct Vector *x, struct Vector *v)
{
	return solveGeneric(iterateEuler, x, v);
}
