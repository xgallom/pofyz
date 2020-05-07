//
// Created by xgallom on 4/9/20.
//

#include "linearLupNormalize.h"
#include "../../core/matrix.h"
#include "../../core/swap.h"
#include "../../core/matrixOperations.h"
#include "../../core/error.h"

void solveLinearLupNormalize(struct Matrix *results, struct Vector *pivots)
{
	fail(results->columns != 1, "LUPN: Input must be row vector: %zu\n", results->columns);
	fail(
			results->rows != pivots->length + 1,
			"LUPN: Pivots should contain one more entry than vector: %zu and %zu\n",
			results->rows, pivots->length + 1
	);

	solveLinearLupNormalizeUnsafe(asMDouble(results), asInt(pivots), results->rows);
}

void solveLinearLupNormalizeUnsafe(double *result, int *pivot, size_t length)
{
	for(size_t index = 0; index < length; ++index)
		for(size_t with = index + 1; with < length; ++with)
			if(pivot[with] == index)
				vectorPivotSwap(result, pivot, index, with, length);
}
