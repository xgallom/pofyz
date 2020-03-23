//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H
#define POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H

#include <stddef.h>
#include <stdint.h>

struct Vector {
	void *data;        // +8B = 8B
	size_t length;     // +8B = 16B
	size_t  entrySize; // +8B = 24B
	const char *type;  // +8B = 32B

	// 64B/32B = 0.5 L1 cache-line
};

struct Vector vectorDouble(size_t length);
size_t resize(struct Vector *vector, size_t newLength);
size_t extend(struct Vector *vector, size_t lengthExtension);
void clear(struct Vector *vector);
void delete(struct Vector *vector);

double *asDouble(struct Vector *vector);
const double *asCDouble(const struct Vector *vector);

#endif //POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H
