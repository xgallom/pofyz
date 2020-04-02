//
// Created by xgallom on 4/2/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H

#include "matrix.h"

struct Matrix transpose(const struct Matrix *matrix);
struct Matrix matrixMultiply(const struct Matrix *left, const struct Matrix *right);

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIXOPERATIONS_H
