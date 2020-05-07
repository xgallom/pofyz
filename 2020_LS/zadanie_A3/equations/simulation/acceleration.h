//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_SIMULATION_ACCELERATION_H
#define POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_SIMULATION_ACCELERATION_H

struct AccelerationData {
	double oldX;
	double oldIntegralT;
};

struct AccelerationData initializeAccelerationData();
double acceleration(double x, double v, struct AccelerationData *data);

#endif //POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_SIMULATION_ACCELERATION_H
