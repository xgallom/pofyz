//
// Created by xgallom on 4/23/20.
//

#include "integrateRiemannSum.h"

double solveIntegrateRiemannSum(IntegralFunction *function, double xMin, double xMax, size_t steps)
{
	const double delta = (xMax - xMin) / steps, origin = xMin + delta / 2.0;

	double sum = 0.0;
	for(size_t n = 0; n < steps; ++n)
		sum += (*function)(origin + n * delta);

	return delta * sum;
}