//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_CORE_ERROR_H
#define POFYZ_2020_LS_ZADANIE_A2_CORE_ERROR_H

void error(const char *message, ...);
void die(const char *message, ...);
void fail(int check, const char *message, ...);

#endif //POFYZ_2020_LS_ZADANIE_A2_CORE_ERROR_H
