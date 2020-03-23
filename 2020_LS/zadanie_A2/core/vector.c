//
// Created by xgallom on 3/18/20.
//

#include "vector.h"
#include "error.h"

#include <stdlib.h>

static const char
		TypeDouble[] = "double",
		TypeNull[] = "NULL";

static void allocate(struct Vector *vector)
{
	fail(vector->data != NULL, "Trying to allocate over existing vector of %s\n", vector->type);

	vector->data = malloc(vector->entrySize * vector->length);

	fail(vector->data == NULL, "Failed to create %s[%zu]\n", vector->type, vector->length);
}

static void reallocate(struct Vector *vector)
{
	fail(vector->data == NULL, "Trying to reallocate unallocated vector of %s\n", vector->type);

	vector->data = realloc(vector->data, vector->entrySize * vector->length);

	fail(vector->data == NULL, "Failed to resize %s[%zu]\n", vector->type, vector->length);
}

static void deallocate(struct Vector *vector)
{
	fail(vector->data == NULL, "Trying to deallocate unallocated vector of %s\n", vector->type);

	free(vector->data);
}

struct Vector vectorDouble(size_t length)
{
	struct Vector result = {
			.data = NULL,
			.length = length,
			.entrySize = sizeof(double),
			.type = TypeDouble,
	};

	allocate(&result);

	return result;
}

size_t resize(struct Vector *vector, size_t newLength)
{
	const size_t oldLength = vector->length;
	vector->length = newLength;

	reallocate(vector);

	return oldLength;
}

size_t extend(struct Vector *vector, size_t lengthExtension)
{
	const size_t oldLength = vector->length;
	vector->length += lengthExtension;

	reallocate(vector);

	return oldLength;
}

void clear(struct Vector *vector)
{
	deallocate(vector);

	vector->length = 0;
	vector->data = NULL;
}

void delete(struct Vector *vector)
{
	deallocate(vector);

	*vector = (struct Vector) {
			.data = NULL,
			.length = 0,
			.entrySize = 0,
			.type = TypeNull,
	};
}

double *asDouble(struct Vector *vector) { return vector->data; }
const double *asCDouble(const struct Vector *vector) { return vector->data; }


