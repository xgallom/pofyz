//
// Created by Milan Gallo on 23/03/2020.
//

#include "statistics.h"
#include "../constants.h"

struct Statistics constructStatistics(const double *x, const double *v, size_t length)
{
	struct Statistics statistics = {
			.statistic = {
					.v_max = v[0],
					.x_vmax = x[0],
			}
	};

	for(int i = 0; i < length; ++i) {
		const double
				x_i = x[i],
				v_i = v[i];

		if(v_i < statistics.statistic.v_max) {
			statistics.statistic.v_max = v_i;
			statistics.statistic.x_vmax = x_i;
		}

		if(x_i <= 0.0) {
			statistics.statistic.t_fall = i * dt;
			statistics.statistic.v_fall = v_i;

			break;
		}
	}

	return statistics;
}
