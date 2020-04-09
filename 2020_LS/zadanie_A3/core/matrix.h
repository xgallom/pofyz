//
// Created by xgallom on 4/2/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIX_H
#define POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIX_H

#include "vector.h"

#define KEEP_SIZE -1

struct Matrix {
	void *data;       // +8B = 8B
	size_t length;    // +8B = 16B
	size_t entrySize; // +8B = 24B
	const char *type; // +8B = 32B

	// 32B/64B = 0.5 L1 cache-line

	size_t rows;      // +8B = 40B
	size_t columns;   // +8B = 48B

	// 48B/64B = 0.75 L1 cache-line
};

typedef void (MatrixIterator)(struct Matrix *matrix, double *value, size_t row, size_t column, void *data);
typedef void (ConstMatrixIterator)(const struct Matrix *matrix,
								   const double *value,
								   size_t row,
								   size_t column, void *data
);

struct Matrix matrixDouble(size_t rows, size_t columns);
struct Matrix matrixDoubleIndex(struct Matrix *into);
struct Matrix matrixRowVectorDouble(size_t columns);
struct Matrix matrixColumnVectorDouble(size_t rows);

struct Matrix matrixCopy(const struct Matrix *from);

size_t matrixResize(struct Matrix *matrix, size_t newRows, size_t newColumns);
void matrixClear(struct Matrix *matrix);
void matrixDelete(struct Matrix *matrix);

int matrixIsNull(const struct Matrix *matrix);
size_t matrixSizeOf(const struct Matrix *matrix);
const char *matrixType(const struct Matrix *matrix);

void iterateImpl(struct Matrix *matrix, MatrixIterator *iterator, void *data);
void iterateConstImpl(const struct Matrix *matrix, ConstMatrixIterator *iterator, void *data);
#define iterate(matrix, iterator, data) iterateImpl(matrix, (MatrixIterator *) iterator, (void *) data)
#define iterateConst(matrix, iterator, data) iterateConstImpl(matrix, (ConstMatrixIterator *) iterator, (void *) data);

double *asMDouble(struct Matrix *matrix);
const double *asCMDouble(const struct Matrix *matrix);
double *asRow(struct Matrix *matrix, size_t row);
const double *asCRow(const struct Matrix *matrix, size_t row);
double getAt(const struct Matrix *matrix, size_t row, size_t column);
double *at(struct Matrix *matrix, size_t row, size_t column);
const double *cAt(const struct Matrix *matrix, size_t row, size_t column);

double **asMDoubleIndex(struct Matrix *matrix);
const double **asCMDoubleIndex(struct Matrix *matrix);

void dumpMatrixImpl(const struct Matrix *matrix, const char *name);
#define dumpMatrix(matrix) dumpMatrixImpl(matrix, #matrix)

#endif //POFYZ_2020_LS_ZADANIE_A3_CORE_MATRIX_H
