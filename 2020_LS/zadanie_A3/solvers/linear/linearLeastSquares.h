//
// Created by xgallom on 4/2/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLEASTSQUARES_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLEASTSQUARES_H

#include "../../core/matrix.h"

struct Matrix solveLinearLeastSquares(const struct Matrix *x, const struct Matrix *y, size_t polynomialSize);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLEASTSQUARES_H
