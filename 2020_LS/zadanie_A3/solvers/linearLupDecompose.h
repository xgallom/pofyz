//
// Created by xgallom on 4/9/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPDECOMPOSE_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPDECOMPOSE_H

#include <stddef.h>

struct Matrix;
struct Vector;

void solveLinearLupDecompose(struct Matrix *matrixIndex, struct Vector *pivots);
void solveLinearLupDecomposeUnsafe(double **index, int *pivot, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPDECOMPOSE_H
