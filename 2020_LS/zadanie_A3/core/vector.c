//
// Created by xgallom on 3/18/20.
//

#include "vector.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char
		*TypeChar = "char",
		*TypeView = "view_char",
		*TypeDouble = "double",
		*TypeDoubleIndex = "double*",
		*TypeInt = "int",
		*TypeNull = "NULL";

static void allocate(struct Vector *vector)
{
	fail(!isNull(vector), "Trying to allocate over existing vector of %s\n", vector->type);

	vector->data = malloc(vector->entrySize * vector->length);

	fail(isNull(vector), "Failed to create %s[%zu]\n", vectorType(vector), vector->length);
}

static void reallocate(struct Vector *vector)
{
	fail(isNull(vector), "Trying to reallocate unallocated vector of %s\n", vectorType(vector));

	vector->data = realloc(vector->data, vector->entrySize * vector->length);

	fail(isNull(vector), "Failed to resize %s[%zu]\n", vectorType(vector), vector->length);
}

static void deallocate(struct Vector *vector)
{
	fail(isNull(vector), "Trying to deallocate unallocated vector of %s\n", vectorType(vector));

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

struct Vector vectorDoubleIndex(size_t length)
{
	struct Vector result = {
			.data = NULL,
			.length = length,
			.entrySize = sizeof(double *),
			.type = TypeDoubleIndex,
	};

	allocate(&result);

	return result;
}

struct Vector vectorInt(size_t length)
{
	struct Vector result = {
			.data = NULL,
			.length = length,
			.entrySize = sizeof(int),
			.type = TypeInt,
	};

	allocate(&result);

	return result;
}

struct Vector string(size_t length)
{
	struct Vector result = {
			.data = NULL,
			.length = length + 1,
			.entrySize = sizeof(char),
			.type = TypeChar,
	};

	allocate(&result);

	return result;
}

struct Vector stringFrom(const char *buffer)
{
	const size_t length = strlen(buffer);
	const struct Vector result = string(length);

	strcpy(result.data, buffer);

	return result;
}

struct Vector stringView(const char *buffer)
{
	return (struct Vector) {
			.data = (char *) buffer,
			.length = strlen(buffer) + 1,
			.entrySize = 0,
			.type = TypeView,
	};
}

struct Vector copy(const struct Vector *from)
{
	struct Vector result = *from;

	result.data = NULL;
	allocate(&result);

	memcpy(result.data, from->data, sizeOf(from));

	return result;
}

size_t resize(struct Vector *vector, size_t newLength)
{
	const size_t oldLength = vector->length;
	vector->length = newLength;

	if(newLength != oldLength) {
		if(!oldLength)
			allocate(vector);
		else
			reallocate(vector);
	}

	return oldLength;
}

size_t extend(struct Vector *vector, size_t lengthExtension)
{
	return resize(vector, vector->length + lengthExtension);
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
	*vector = NULL_VECTOR;
}

int isNull(const struct Vector *vector) { return vector->data == NULL; }
size_t sizeOf(const struct Vector *vector) { return vector->entrySize * vector->length; }
const char *vectorType(const struct Vector *vector) { return vector->type ? vector->type : TypeNull; }

double *asDouble(struct Vector *vector) { return vector->data; }
const double *asCDouble(const struct Vector *vector) { return vector->data; }

int *asInt(struct Vector *vector) { return vector->data; }
const int *asCInt(const struct Vector *vector) { return vector->data; }

char *asString(struct Vector *vector) { return vector->data; }
const char *asCString(const struct Vector *vector) { return vector->data; }

void dumpVectorImpl(const struct Vector *vector, const char *name)
{
	printf(
			"Vector \"%s\" of %s[%zu]:\n"
			"    ",
			name,
			vectorType(vector),
			vector->length
	);

	if(vector->type == TypeInt) {
		const int *value = asCInt(vector);
		for(size_t index = 0; index < vector->length; ++index)
			printf("%d ", *value++);
	}

	printf("\n\n");
}
