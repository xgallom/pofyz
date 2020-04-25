//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
#define POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H

#include <math.h>

// SIMULATION PARAMETERS
extern double
		x_0,
		v_0,
		dt;

// OBJECT PARAMETERS
extern double
		m,
		S,
		C;

// FIXED CONSTANT PARAMETERS
#define BATCH_SIZE   (1u << 10u)
#define SIMULATION_LENGTH_LIMIT ((1u << 30u) / (sizeof(double) * 2))
#define INTEGRAL_STEPS (1u << 11u)

#define g       9.80665
#define R       8.3144598
#define p_0     101.325e3

#define M_N2    0.028
#define M_O2    0.032
#define p_N2    0.788
#define p_O2    (1.0 - p_N2)

#define M       (p_N2 * M_N2 + p_O2 * M_O2)

struct Arguments;
void initializeConstants(const struct Arguments *arguments);

#endif //POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
