//
// Created by xgallom on 4/2/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H

#include "matrix.h"

struct Matrix transpose(const struct Matrix *matrix);
struct Matrix matrixMultiply(const struct Matrix *left, const struct Matrix *right);
struct Matrix matrixVectorReverse(const struct Matrix *vector);

void matrixPivotSwap(double **index, int *pivot, size_t rowA, size_t rowB, size_t length);
void vectorPivotSwap(double *vector, int *pivot, size_t indexA, size_t indexB, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H
