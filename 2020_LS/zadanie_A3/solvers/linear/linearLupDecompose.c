//
// Created by xgallom on 4/9/20.
//

#include "linearLupDecompose.h"
#include "../../core/matrix.h"
#include "../../core/error.h"
#include "../../core/matrixOperations.h"

#include <math.h>

#define TOLERANCE 1e-20

static size_t findMaximumPivotRow(size_t diagonal, double **index, size_t length)
{
	double maximum = 0.0;
	size_t maximumRow = diagonal;

	for(size_t row = diagonal; row < length; ++row) {
		const double absolute = fabs(index[row][diagonal]);

		if(absolute > maximum) {
			maximum = absolute;
			maximumRow = row;
		}
	}

	fail(maximum < TOLERANCE, "LUP: Failed to decompose, matrix is degenerate\n");

	return maximumRow;
}

void solveLinearLupDecompose(struct Matrix *matrixIndex, struct Vector *pivots)
{
	fail(
			matrixIndex->rows != matrixIndex->columns,
			"LUPD: Input must be square matrix: %zu and %zu\n", matrixIndex->rows, matrixIndex->columns
	);
	fail(
			matrixIndex->rows != pivots->length + 1,
			"LUPD: Pivots should contain one more entry than matrix: %zu and %zu\n",
			matrixIndex->rows, pivots->length + 1
	);

	solveLinearLupDecomposeUnsafe(asMDoubleIndex(matrixIndex), asInt(pivots), matrixIndex->rows);
}

void solveLinearLupDecomposeUnsafe(double **index, int *pivot, size_t length)
{
	for(size_t diagonal = 0; diagonal < length; ++diagonal) {
		size_t pivotRow = findMaximumPivotRow(diagonal, index, length);

		if(pivotRow != diagonal)
			matrixPivotSwap(index, pivot, diagonal, pivotRow, length);

		for(size_t row = diagonal + 1; row < length; ++row) {
			index[row][diagonal] /= index[diagonal][diagonal];

			for(size_t column = diagonal + 1; column < length; ++column)
				index[row][column] -= index[row][diagonal] * index[diagonal][column];
		}
	}
}
