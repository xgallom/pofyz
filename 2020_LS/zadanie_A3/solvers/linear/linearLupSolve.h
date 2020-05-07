//
// Created by xgallom on 4/9/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPSOLVE_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPSOLVE_H

#include <stddef.h>

struct Matrix;
struct Vector;

void solveLinearLupSolve(
		struct Matrix *restrict matrixIndex,
		struct Matrix *restrict results,
		const struct Matrix *restrict values,
		const struct Vector *pivots
);
void solveLinearLupSolveUnsafe(
		double **index,
		double *result,
		const double *value,
		const int *pivot,
		size_t length
);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEARLUPSOLVE_H
