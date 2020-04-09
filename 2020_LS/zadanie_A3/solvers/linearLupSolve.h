//
// Created by xgallom on 4/9/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPSOLVE_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPSOLVE_H

struct Matrix;
struct Vector;

void solveLinearLupSolve(
		struct Matrix *matrixIndex,
		struct Matrix *results,
		struct Matrix *values,
		struct Vector *pivots);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEARLUPSOLVE_H
