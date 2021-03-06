//
// Created by xgallom on 4/2/20.
//

#include "matrixOperations.h"
#include "error.h"
#include "swap.h"

struct Matrix transpose(const struct Matrix *matrix)
{
	const size_t rows = matrix->columns, columns = matrix->rows;

	struct Matrix result = matrixDouble(rows, columns);

	const double *source = asCMDouble(matrix);

	for(size_t column = 0; column < columns; ++column) {
		for(size_t row = 0; row < rows; ++row)
			*at(&result, row, column) = *source++;
	}

	return result;
}

struct MatrixMultiplyIteratorData {
	const struct Matrix *left, *right;
};

void matrixMultiplyIterator(
		struct Matrix *matrix,
		double *value,
		size_t row,
		size_t column,
		const struct MatrixMultiplyIteratorData *data)
{
	const size_t count = data->left->columns;
	const double *leftRow = asCRow(data->left, row);

	double result = 0.0;
	for(size_t i = 0; i < count; ++i)
		result += *leftRow++ * *cAt(data->right, i, column);

	*value = result;
}

struct Matrix matrixMultiply(const struct Matrix *left, const struct Matrix *right)
{
	fail(left->columns != right->rows, "Matrix multiply size mismatch: %zu and %zu\n", left->columns, right->rows);

	struct Matrix result = matrixDouble(left->rows, right->columns);

	const struct MatrixMultiplyIteratorData iteratorData = {
			.left = left,
			.right = right,
	};
	iterate(&result, matrixMultiplyIterator, &iteratorData);

	return result;
}

void matrixVectorReverseIterator(
		struct Matrix *matrix,
		double *value,
		size_t row,
		size_t column,
		const struct Matrix *vector)
{
	*value = asCMDouble(vector)[vector->length - row - column - 1];
}

struct Matrix matrixVectorReverse(const struct Matrix *vector)
{
	struct Matrix result = matrixDouble(vector->rows, vector->columns);

	iterate(&result, matrixVectorReverseIterator, vector);

	return result;
}

void matrixPivotSwap(double **index, int *pivot, size_t rowA, size_t rowB, size_t length)
{
	swap(int, pivot[rowA], pivot[rowB])
	swap(double *, index[rowA], index[rowB])

	// For determinant
	++pivot[length];
}

void vectorPivotSwap(double *vector, int *pivot, size_t indexA, size_t indexB, size_t length)
{
	swap(int, pivot[indexA], pivot[indexB])
	swap(double, vector[indexA], vector[indexB])

	// For determinant
	++pivot[length];
}
