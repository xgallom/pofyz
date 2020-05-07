//
// Created by xgallom on 4/9/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPNORMALIZE_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPNORMALIZE_H

#include <stddef.h>

struct Matrix;
struct Vector;

void solveLinearLupNormalize(struct Matrix *results, struct Vector *pivots);
void solveLinearLupNormalizeUnsafe(double *result, int *pivot, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPNORMALIZE_H
