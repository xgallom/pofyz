//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_PARSE_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_PARSE_H

#include <stddef.h>

int parseInt(const char *string);
size_t parseInts(const char *string, int *buffer, size_t count);

double parseDouble(const char *string);
size_t parseDoubles(const char *string, double *buffer, size_t count);

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_PARSE_H
