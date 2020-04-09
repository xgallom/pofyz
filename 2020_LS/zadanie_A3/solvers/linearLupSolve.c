//
// Created by xgallom on 4/9/20.
//

#include "linearLupSolve.h"
#include "../core/matrix.h"

void solveLinearLupSolve(
		struct Matrix *matrixIndex,
		struct Matrix *results,
		struct Matrix *values,
		struct Vector *pivots)
{
	const size_t length = matrixIndex->rows;
	double **index = asMDoubleIndex(matrixIndex);
	double *result = asMDouble(results);
	double *value = asMDouble(values);
	int *pivot = asInt(pivots);

	for(size_t diagonal = 0; diagonal < length; ++diagonal) {
		result[diagonal] = value[pivot[diagonal]];

		for(size_t column = 0; column < diagonal; ++column)
			result[diagonal] -= index[diagonal][column] * result[column];
	}

	for(int diagonal = (int) length - 1; diagonal >= 0; --diagonal) {
		for(size_t column = diagonal + 1; column < length; ++column)
			result[diagonal] -= index[diagonal][column] * result[column];

		result[diagonal] /= index[diagonal][diagonal];
	}
}
