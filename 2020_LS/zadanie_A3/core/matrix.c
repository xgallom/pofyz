//
// Created by xgallom on 4/2/20.
//

#include "matrix.h"
#include "vector.h"

#include <stdio.h>

struct Matrix matrixDouble(size_t rows, size_t columns)
{
	struct Matrix result = {
			.rows = rows,
			.columns = columns
	};

	*((struct Vector *) &result) = vectorDouble(rows * columns);

	return result;
}

struct Matrix matrixDoubleIndex(struct Matrix *into)
{
	struct Matrix result = {
			.rows = into->rows,
			.columns = into->columns,
	};

	*((struct Vector *) &result) = vectorDoubleIndex(into->rows);

	double **index = asMDoubleIndex(&result);
	for(size_t row = 0; row < into->rows; ++row)
		*index++ = asRow(into, row);

	return result;
}

struct Matrix matrixRowVectorDouble(size_t columns) { return matrixDouble(1, columns); }
struct Matrix matrixColumnVectorDouble(size_t rows) { return matrixDouble(rows, 1); }

struct Matrix matrixCopy(const struct Matrix *from)
{
	struct Matrix result = {
			.rows = from->rows,
			.columns = from->columns
	};

	*((struct Vector *) &result) = copy((const struct Vector *) from);

	return result;
}

size_t matrixResize(struct Matrix *matrix, size_t newRows, size_t newColumns)
{
	matrix->rows = newRows == KEEP_SIZE ? matrix->rows : newRows;
	matrix->columns = newColumns == KEEP_SIZE ? matrix->columns : newColumns;

	return resize((struct Vector *) matrix, matrixSizeOf(matrix));
}
void matrixClear(struct Matrix *matrix)
{
	matrix->rows = matrix->columns = 0;
	clear((struct Vector *) matrix);
}
void matrixDelete(struct Matrix *matrix)
{
	matrix->rows = matrix->columns = 0;
	delete((struct Vector *) matrix);
}

int matrixIsNull(const struct Matrix *matrix) { return isNull((const struct Vector *) matrix); }
size_t matrixSizeOf(const struct Matrix *matrix) { return matrix->rows * matrix->columns; }
const char *matrixType(const struct Matrix *matrix) { return vectorType((const struct Vector *) matrix); }

void iterateImpl(struct Matrix *matrix, MatrixIterator *iterator, void *data)
{
	double *value = asMDouble(matrix);

	for(size_t row = 0; row < matrix->rows; ++row) {
		for(size_t column = 0; column < matrix->columns; ++column)
			(*iterator)(matrix, value++, row, column, data);
	}
}

void iterateConstImpl(const struct Matrix *matrix, ConstMatrixIterator *iterator, void *data)
{
	const double *value = asCMDouble(matrix);

	for(size_t row = 0; row < matrix->rows; ++row) {
		for(size_t column = 0; column < matrix->columns; ++column)
			(*iterator)(matrix, value++, row, column, data);
	}
}

double *asMDouble(struct Matrix *matrix) { return asDouble((struct Vector *) matrix); }
const double *asCMDouble(const struct Matrix *matrix) { return asCDouble((const struct Vector *) matrix); }
double *asRow(struct Matrix *matrix, size_t row) { return asMDouble(matrix) + row * matrix->columns; }
const double *asCRow(const struct Matrix *matrix, size_t row) { return asCMDouble(matrix) + row * matrix->columns; }
double getAt(const struct Matrix *matrix, size_t row, size_t column) { return *cAt(matrix, row, column); }
double *at(struct Matrix *matrix, size_t row, size_t column) { return asRow(matrix, row) + column; }
const double *cAt(const struct Matrix *matrix, size_t row, size_t column) { return asCRow(matrix, row) + column; }

double **asMDoubleIndex(struct Matrix *matrix) { return matrix->data; }
const double **asCMDoubleIndex(struct Matrix *matrix) { return matrix->data; }

void dumpMatrixImpl(const struct Matrix *matrix, const char *name)
{
	const double *value = asCMDouble(matrix);

	printf(
			"Matrix \"%s\" of %s[%zu, %zu]:\n"
			"    ",
			name,
			matrixType(matrix),
			matrix->rows,
			matrix->columns
	);

	for(size_t row = 0; row < matrix->rows; ++row) {
		for(size_t column = 0; column < matrix->columns; ++column)
			printf("%+6.3e ", *value++);

		printf("\n    ");
	}
	printf("\n");
}
