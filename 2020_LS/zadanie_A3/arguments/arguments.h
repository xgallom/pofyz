//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
#define POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H

#include "parameters.h"
#include "options.h"
#include "dataFiles.h"
#include "../core/vector.h"

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

	union {
		int options[OPTION_COUNT];
		struct {
			int
					polynomialDegree;
		} option;
	};

	union {
		struct Vector dataFiles[DATAFILE_COUNT];
		struct {
			struct Vector
					temperature;
		} dataFile;
	};
};

struct Arguments parseArguments(int argc, char *argv[]);
void dumpArguments(const struct Arguments *arguments);

#endif //POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
