//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
#define POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H

#include "arguments.h"

#include <math.h>

#define steps   500

// SIMULATION PARAMETERS
extern double
		x_0,
		v_0,
		dt;

// OBJECT PARAMETERS
extern double
		m,
		S,
		C,
		T;

// CALCULATED CONSTANT PARAMETERS
extern double
		ro_0,
		K_0,
		v_inf2,
		v_inf,
		kappa;

#define g       9.80665
#define R       8.3144598
#define p_0     101.325e3

#define M_N2    0.028
#define M_O2    0.032
#define p_N2    0.788
#define p_O2    (1.0 - p_N2)

#define M       (p_N2 * M_N2 + p_O2 * M_O2)
#define K(x)    (K_0 * exp(-kappa * (x)))

void initializeConstants(struct Arguments arguments);

#endif //POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
