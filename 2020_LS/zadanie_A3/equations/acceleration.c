//
// Created by xgallom on 3/12/20.
//

#include "acceleration.h"
#include "../constants.h"
#include "dynamics.h"
#include "../solvers/integrateRiemannSum.h"
#include "../data/temperature.h"

static double reciprocalTemperatureFor(double x)
{
	return 1. / temperatureFor(x);
}

struct AccelerationData initializeAccelerationData()
{
	return (struct AccelerationData) {
			.oldX = x_0,
			.oldIntegralT = solveIntegrateRiemannSum(reciprocalTemperatureFor, 0.0, x_0, INTEGRAL_STEPS)
	};
}

double acceleration(double x, double v, struct AccelerationData *data)
{
	return -g + K(x, solveStepRiemannSum(reciprocalTemperatureFor, &data->oldX, x, &data->oldIntegralT)) * v * v;
}
