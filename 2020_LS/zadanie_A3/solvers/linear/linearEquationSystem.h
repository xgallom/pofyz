//
// Created by xgallom on 4/9/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEAREQUATIONSYSTEM_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEAREQUATIONSYSTEM_H

struct Matrix;
struct Vector;

struct Matrix solveLinearEquationSystem(struct Matrix *transformationMatrix, struct Matrix *values);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_LINEAR_LINEAREQUATIONSYSTEM_H
