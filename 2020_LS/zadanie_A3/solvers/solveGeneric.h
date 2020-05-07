//
// Created by Milan Gallo on 23/03/2020.
//

#ifndef POFYZ_SOLVEGENERIC_H
#define POFYZ_SOLVEGENERIC_H

#include <stddef.h>

struct Vector;
struct AccelerationData;
typedef void (SolverIterator)(double *restrict x, double *restrict v, size_t length, struct AccelerationData *data);

size_t solveGeneric(SolverIterator solver, struct Vector *restrict x_vec, struct Vector *restrict v_vec);

#endif //POFYZ_SOLVEGENERIC_H
