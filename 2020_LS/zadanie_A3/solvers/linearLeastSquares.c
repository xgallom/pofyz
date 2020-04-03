//
// Created by xgallom on 4/2/20.
//

#include "linearLeastSquares.h"
#include "../core/error.h"
#include "../core/matrixOperations.h"
#include "../equations/polynomial.h"

#include <stdio.h>

void createTransformationMatrix(
		struct Matrix *matrix,
		double *value,
		size_t row,
		size_t column,
		const struct Matrix *x)
{
	*value = nthDegreePolynomial(getAt(x, 0, row), column);
}

struct Matrix solveLinearLeastSquares(const struct Matrix *x, const struct Matrix *y, size_t polynomialSize)
{
	fail(x->rows != y->rows, "LLS: Input vector size mismatch: %zu and %zu\n", x->rows, y->rows);
	fail(x->columns != 1 || y->columns != 1, "LLS: Input must be row vectors: %zu and %zu\n", x->columns, y->columns);

	const size_t dataSize = x->rows;

	struct Matrix coefficients = matrixColumnVectorDouble(polynomialSize);

	struct Matrix transformationMatrix = matrixDouble(dataSize, polynomialSize);
	iterate(&transformationMatrix, createTransformationMatrix, x);
	printf("X:\n");
	dumpMatrix(&transformationMatrix);

	struct Matrix transposedTransformationMatrix = transpose(&transformationMatrix);

	struct Matrix cubicTransformationMatrix = matrixMultiply(&transposedTransformationMatrix, &transformationMatrix);
	printf("XTX:\n");
	dumpMatrix(&cubicTransformationMatrix);

	matrixDelete(&transformationMatrix);

	struct Matrix transformedValues = matrixMultiply(&transposedTransformationMatrix, y);
	printf("XTy:\n");
	dumpMatrix(&transformedValues);

	matrixDelete(&transposedTransformationMatrix);

	matrixDelete(&cubicTransformationMatrix);
	matrixDelete(&transformedValues);

	return coefficients;
}
