//
// Created by xgallom on 3/12/20.
//

#include "acceleration.h"
#include "constants.h"

double acceleration(double x, double v)
{
	return -g + K(x) * v * v;
}
