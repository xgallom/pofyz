//
// Created by xgallom on 3/12/20.
//

#include "acceleration.h"
#include "../constants.h"
#include "dynamics.h"

double acceleration(double x, double v, struct AccelerationData *data)
{
	return -g + K(x, &data->oldX, &data->oldIntegralT) * v * v;
}
