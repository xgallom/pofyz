//
// Created by Milan Gallo on 23/03/2020.
//

#include "statistics.h"
#include "../../constants.h"

struct Statistics constructStatistics(const double *restrict x, const double *restrict v, size_t length)
{
	struct Statistics statistics = {
			.statistic = {
					.v_max = v[0],
					.x_vmax = x[0],
			}
	};

	const double xFinal = x_land;

	for(int i = 0; i < length; ++i) {
		const double
				x_i = x[i],
				v_i = v[i];

		if(v_i < statistics.statistic.v_max) {
			statistics.statistic.t_vmax = i * dt;
			statistics.statistic.x_vmax = x_i;
			statistics.statistic.v_max = v_i;
		}

		if(x_i <= xFinal) {
			statistics.statistic.t_fall = i * dt;
			statistics.statistic.x_fall = x_i;
			statistics.statistic.v_fall = v_i;

			break;
		}
	}

	return statistics;
}

