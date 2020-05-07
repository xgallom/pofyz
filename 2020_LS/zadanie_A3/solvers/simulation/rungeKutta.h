//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_RUNGEKUTTA_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_RUNGEKUTTA_H

#include <stddef.h>

struct Vector;

size_t solveRungeKutta(struct Vector *restrict x, struct Vector *restrict v);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_RUNGEKUTTA_H
