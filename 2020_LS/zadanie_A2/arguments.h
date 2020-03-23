//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
#define POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H

// SIMULATION PARAMETERS
#define PARAMETER_x_0     0
#define PARAMETER_v_0     1
#define PARAMETER_dt      2

// OBJECT PARAMETERS
#define PARAMETER_m       3
#define PARAMETER_S       4
#define PARAMETER_C       5
#define PARAMETER_T       6

// PARAMETER_CONTROL
#define PARAMETER_INVALID -1
#define PARAMETER_COUNT   7

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

#endif //POFYZ_2020_LS_ZADANIE_A2_ARGUMENTS_H
