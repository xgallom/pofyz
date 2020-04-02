//
// Created by xgallom on 4/2/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_POLYNOMIAL_H
#define POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_POLYNOMIAL_H

#include <stddef.h>

struct Matrix;

double nthDegreePolynomial(double x, size_t n);
double computePolynomial(double x, const struct Matrix *coefficients);

#endif //POFYZ_2020_LS_ZADANIE_A3_EQUATIONS_POLYNOMIAL_H
