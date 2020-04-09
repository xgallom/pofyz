//
// Created by xgallom on 3/18/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H
#define POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H

#include <stddef.h>
#include <stdint.h>

struct Vector {
	void *data;       // +8B = 8B
	size_t length;    // +8B = 16B
	size_t entrySize; // +8B = 24B
	const char *type; // +8B = 32B

	// 32B/64B = 0.5 L1 cache-line
};

#define NULL_VECTOR (struct Vector) {.data = NULL, .length = 0, .entrySize = 0, .type = NULL}

struct Vector vectorDouble(size_t length);
struct Vector vectorInt(size_t length);
struct Vector string(size_t length);
struct Vector stringFrom(const char *buffer);
struct Vector stringView(const char *buffer);

struct Vector copy(const struct Vector *from);

size_t resize(struct Vector *vector, size_t newLength);
size_t extend(struct Vector *vector, size_t lengthExtension);
void clear(struct Vector *vector);
void delete(struct Vector *vector);

int isNull(const struct Vector *vector);
size_t sizeOf(const struct Vector *vector);
const char *vectorType(const struct Vector *vector);

double *asDouble(struct Vector *vector);
const double *asCDouble(const struct Vector *vector);

int *asInt(struct Vector *vector);
const int *asCInt(const struct Vector *vector);

char *asString(struct Vector *vector);
const char *asCString(const struct Vector *vector);

#endif //POFYZ_2020_LS_ZADANIE_A2_CORE_VECTOR_H
