//
// Created by Milan Gallo on 23/03/2020.
//

#include "solveGeneric.h"
#include "../core/vector.h"
#include "../constants.h"

size_t solveGeneric(SolverIterator solver, struct Vector *x_vec, struct Vector *v_vec)
{
	asDouble(x_vec)[0] = x_0;
	asDouble(v_vec)[0] = v_0;

	size_t
			start = 0,
			length = x_vec->length;

	for(;;) {
		double
				*const x = asDouble(x_vec),
				*const v = asDouble(v_vec);

		solver(x + start, v + start, length - start);

		if(x[length - 1] <= 0.0)
			break;

		start = resize(x_vec, (length += steps)) - 1;
		resize(v_vec, length);
	}

	return length;
}
