//
// Created by Milan Gallo on 23/03/2020.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_STATISTICS_H
#define POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_STATISTICS_H

#include <stddef.h>

#define STATISTIC_t_fall 0
#define STATISTIC_x_fall 1
#define STATISTIC_v_fall 2

#define STATISTIC_t_vmax 3
#define STATISTIC_x_vmax 4
#define STATISTIC_v_max  5

#define STATISTIC_COUNT  6

struct Statistics {
	union {
		double statistics[STATISTIC_COUNT];
		struct {
			double
					t_fall,
					x_fall,
					v_fall,

					t_vmax,
					x_vmax,
					v_max;
		} statistic;
	};
};

struct Statistics constructStatistics(const double *restrict x, const double *restrict v, size_t length);

#endif //POFYZ_2020_LS_ZADANIE_A3_SOLVERS_SIMULATION_STATISTICS_H
