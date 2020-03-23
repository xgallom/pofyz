//
// Created by Milan Gallo on 23/03/2020.
//

#ifndef POFYZ_STATISTICS_H
#define POFYZ_STATISTICS_H

#include <stddef.h>

#define STATISTIC_t_fall 0
#define STATISTIC_v_fall 1
#define STATISTIC_v_max  2
#define STATISTIC_z_vmax 3

#define STATISTIC_COUNT  4

struct Statistics {
	union {
		double statistics[STATISTIC_COUNT];
		struct {
			double
					t_fall,
					v_fall,
					v_max,
					x_vmax;
		} statistic;
	};
};

struct Statistics constructStatistics(const double *x, const double *v, size_t length);

#endif //POFYZ_STATISTICS_H
