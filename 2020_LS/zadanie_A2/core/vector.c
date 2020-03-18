//
// Created by xgallom on 3/18/20.
//

#include "vector.h"
#include "error.h"

#include <stdlib.h>

double *vectorDouble(size_t length)
{
	double *result = malloc(sizeof(double) * length);

	fail(result == NULL, "Failed to create double[%zu]\n", length);

	return result;
}

void deleteVector(void **vector)
{
	free(*vector);
	*vector = NULL;
}
