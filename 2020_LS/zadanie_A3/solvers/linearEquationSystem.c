//
// Created by xgallom on 4/9/20.
//

#include "linearLeastSquares.h"
#include "../core/matrix.h"
#include "../core/error.h"
#include "linearLupDecompose.h"
#include "linearLupSolve.h"
#include "linearLupNormalize.h"

static struct Vector preparePivots(size_t length)
{
	struct Vector pivots = vectorInt(length + 1);

	int *pivot = asInt(&pivots);
	for(int n = 0; n < pivots.length; ++n)
		*pivot++ = n;

	return pivots;
}

struct Matrix solveLinearEquationSystem(struct Matrix *transformationMatrix, struct Matrix *values)
{
	fail(values->columns != 1, "LES: Input must be row vector: %zu\n", values->columns);
	fail(
			transformationMatrix->rows != transformationMatrix->columns,
			"LES: Input must be square matrix: %zu and %zu\n", transformationMatrix->rows, transformationMatrix->columns
	);
	fail(
			transformationMatrix->rows != values->rows,
			"LES: Input matrix size mismatch: %zu and %zu\n", transformationMatrix->rows, values->rows
	);

	const size_t length = transformationMatrix->rows;

	struct Matrix transformationMatrixIndex = matrixDoubleIndex(transformationMatrix);
	struct Matrix result = matrixColumnVectorDouble(length);
	struct Vector pivots = preparePivots(length);

	solveLinearLupDecompose(&transformationMatrixIndex, &pivots);
	solveLinearLupSolve(&transformationMatrixIndex, &result, values, &pivots);
	solveLinearLupNormalize(&result, &pivots);

	matrixDelete(&transformationMatrixIndex);
	delete(&pivots);

	return result;
}
