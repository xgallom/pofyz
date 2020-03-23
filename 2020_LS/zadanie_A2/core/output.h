//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_CORE_OUTPUT_H
#define POFYZ_2020_LS_ZADANIE_A2_CORE_OUTPUT_H

#include <stddef.h>
#include <stdio.h>

void outputDouble(const char *filePath, const double *vector, size_t length);
void outputDoubles(const char *filePath, const double *vector1, const double *vector2, size_t length);
void outputRow(FILE *outputFile, double index, const double *vector, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A2_CORE_OUTPUT_H
