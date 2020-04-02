//
// Created by xgallom on 3/25/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_DATA_TEMPERATURE_H
#define POFYZ_2020_LS_ZADANIE_A3_DATA_TEMPERATURE_H

#include <stddef.h>

struct Arguments;
struct Matrix;

void initializeTemperature(const struct Arguments *arguments);
void cleanupTemperature(void);

const struct Matrix *temperaturePositions();
const struct Matrix *temperatureValues();
size_t temperatureCount();

void dumpTemperature(void);

#endif //POFYZ_2020_LS_ZADANIE_A3_DATA_TEMPERATURE_H
