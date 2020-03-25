//
// Created by Milan Gallo on 24/03/2020.
//

#ifndef POFYZ_PARAMETERTABLES_H
#define POFYZ_PARAMETERTABLES_H

#include "parameters.h"

#define PARAMETERS_DETAILS_UNIT  0
#define PARAMETERS_DETAILS_DESC  1
#define PARAMETERS_DETAILS_COUNT 2

extern const char *ParametersTable[PARAMETER_COUNT];
extern const char *ParametersDetailsTable[PARAMETER_COUNT][PARAMETERS_DETAILS_COUNT];

#endif //POFYZ_PARAMETERTABLES_H
