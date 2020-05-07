//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
#define POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H

#include "parameters.h"
#include "intOptions.h"
#include "stringOptions.h"
#include "../core/vector.h"

#define HELP_ARGUMENT "--help"

struct Arguments {
	union {
		double parameters[PARAMETER_COUNT];
		struct {
			double
					x_0,
					x_land,
					v_0,
					dt,

					m,
					x_open,
					x_max,
					S_0,
					S_max,
					C_0,
					C_max;
		} parameter;
	};

	union {
		int intOptions[INTOPTION_COUNT];
		struct {
			int
					polynomialDegree;
		} intOption;
	};

	union {
		struct Vector stringOptions[STRINGOPTION_COUNT];
		struct {
			struct Vector
					temperature,
					name;
		} stringOption;
	};
};

struct Arguments parseArguments(int argc, char *argv[]);

#include "dumpArguments.h"

#endif //POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
