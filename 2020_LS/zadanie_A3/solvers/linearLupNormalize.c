//
// Created by xgallom on 4/9/20.
//

#include "linearLupNormalize.h"
#include "../core/matrix.h"
#include "../core/swap.h"
#include "../core/matrixOperations.h"

void solveLinearLupNormalize(struct Matrix *results, struct Vector *pivots)
{
	const size_t length = results->rows;
	double *result = asMDouble(results);
	int *pivot = asInt(pivots);

	for(size_t index = 0; index < length; ++index)
		for(size_t with = index + 1; with < length; ++with)
			if(pivot[with] == index)
				vectorPivotSwap(result, pivot, index, with, length);
}
