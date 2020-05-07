//
// Created by xgallom on 4/23/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_INTEGRATERIEMANNSUM_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_INTEGRATERIEMANNSUM_H

#include <stddef.h>

typedef double (IntegralFunction)(double x);

double solveIntegrateRiemannSum(IntegralFunction function, double xMin, double xMax, size_t steps);
double solveStepRiemannSum(IntegralFunction function, double *restrict oldX, double x, double *restrict oldY);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_INTEGRATERIEMANNSUM_H
