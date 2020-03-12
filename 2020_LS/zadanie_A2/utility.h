//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A_UTILITY_H
#define POFYZ_2020_LS_ZADANIE_A_UTILITY_H

#include <stddef.h>
#include <stdio.h>

void die(const char *message);
void fail(int check, const char *message);

FILE *file(const char *filePath, const char *flags);
void fileClose(FILE *file);

double *vectorDouble(size_t length);
void outputDouble(const char *filePath, const double *vector, size_t length);
void outputDoubles(const char *filePath, const double *vector1, const double *vector2, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A_UTILITY_H
