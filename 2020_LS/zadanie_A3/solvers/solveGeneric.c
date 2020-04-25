//
// Created by Milan Gallo on 23/03/2020.
//

#include "solveGeneric.h"
#include "../core/vector.h"
#include "../constants.h"
#include "../core/error.h"
#include "../equations/acceleration.h"
#include "integrateRiemannSum.h"
#include "../equations/dynamics.h"

#include <stdio.h>

size_t solveGeneric(SolverIterator solver, struct Vector *x_vec, struct Vector *v_vec)
{
	asDouble(x_vec)[0] = x_0;
	asDouble(v_vec)[0] = v_0;

	size_t
			start = 0,
			length = x_vec->length;

	struct AccelerationData data = {
			.oldX = x_0,
			.oldIntegralT = solveIntegrateRiemannSum(reciprocalTemperatureFor, 0.0, x_0, 2048)
	};

	for(;;) {
		double
				*const x = asDouble(x_vec),
				*const v = asDouble(v_vec);

		solver(x + start, v + start, length - start, &data);

		const double lastLength = x[length - 1];

		printf("Height: %f m\n", lastLength);

		if(lastLength <= 0.0)
			break;

		start = resize(x_vec, (length += BATCH_SIZE)) - 1;
		resize(v_vec, length);

		fail(length >= SIMULATION_LENGTH_LIMIT, "Simulation length limit exceeded\n");
	}

	return length;
}
