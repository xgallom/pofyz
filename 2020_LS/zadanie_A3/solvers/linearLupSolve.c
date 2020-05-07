//
// Created by xgallom on 4/9/20.
//

#include "linearLupSolve.h"
#include "../core/matrix.h"
#include "../core/error.h"

void solveLinearLupSolve(
		struct Matrix *restrict matrixIndex,
		struct Matrix *restrict results,
		const struct Matrix *restrict values,
		const struct Vector *pivots)
{
	fail(
			matrixIndex->rows != matrixIndex->columns,
			"LUPS: Input must be square matrix: %zu and %zu\n", matrixIndex->rows, matrixIndex->columns
	);
	fail(
			results->rows != values->rows,
			"LUPS: Input vector size mismatch: %zu and %zu\n", results->rows, values->rows
	);
	fail(
			matrixIndex->rows != values->rows,
			"LUPS: Input matrix size mismatch: %zu and %zu\n", matrixIndex->rows, values->rows
	);
	fail(results->columns != 1 || values->columns != 1,
		 "LUPS: Input must be row vectors: %zu and %zu\n", results->columns, values->columns
	);
	fail(
			matrixIndex->rows != pivots->length + 1,
			"LUPS: Pivots should contain one more entry than matrix: %zu and %zu\n",
			matrixIndex->rows, pivots->length + 1
	);

	solveLinearLupSolveUnsafe(
			asMDoubleIndex(matrixIndex),
			asMDouble(results),
			asCMDouble(values),
			asCInt(pivots),
			matrixIndex->rows
	);
}

void solveLinearLupSolveUnsafe(double **index, double *result, const double *value, const int *pivot, size_t length)
{
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
