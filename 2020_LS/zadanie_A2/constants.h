//
// Created by xgallom on 3/12/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
#define POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H

#include <math.h>

#define steps   500

#define x_0     80.0
#define v_0     0.0
#define dt      0.01

#define g       9.80665
#define m       80.0
#define S       0.2
#define C       0.8
#define R       8.3144598
#define p_0     101.325e3
#define T       293.15
#define M_N2    0.028
#define M_O2    0.032
#define p_N2    0.788
#define p_O2    (1.0 - p_N2)

#define M       (p_N2 * M_N2 + p_O2 * M_O2)

#define ro_0    (M * p_0 / (R * T))
#define K_0     (0.5 * C * S * ro_0 / m)

#define v_inf2  (g / K_0)
#define v_inf() sqrt(v_inf2)

#define kappa   (M * g / (R * T))
#define K(x)    (K_0 * exp(-kappa * x))

#endif //POFYZ_2020_LS_ZADANIE_A_CONSTANTS_H
