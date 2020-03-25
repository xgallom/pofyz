//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
#define POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H

#include "parameters.h"

struct Arguments {
	union {
		double parameters[PARAMETER_COUNT];
		struct {
			double
					x_0,
					v_0,
					dt,

					m,
					S,
					C,
					T;
		} parameter;
	};
};

struct Arguments parseArguments(int argc, char *argv[]);
void dumpParameters(const struct Arguments *arguments);

#endif //POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
