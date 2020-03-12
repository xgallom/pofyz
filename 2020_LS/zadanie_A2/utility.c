//
// Created by xgallom on 3/12/20.
//

#include <stdlib.h>

#include "utility.h"
#include "constants.h"

void die(const char *message)
{
	perror(message);
	abort();
}

void fail(int check, const char *message)
{
	if(check)
		die(message);
}

FILE *file(const char *filePath, const char *flags)
{
	FILE *result = fopen(filePath, flags);

	fail(result == NULL, "Failed to open file\n");

	return result;
}

void close(FILE *file)
{
	fail(fclose(file) != 0, "Failed to close file\n");
}

double *vectorDouble(size_t length)
{
	double *result = malloc(sizeof(double) * length);

	fail(result == NULL, "Failed to create vector of double\n");

	return result;
}

void outputDouble(const char *filePath, const double *vector, size_t length)
{
	FILE *outputFile = file(filePath, "wt");

	for(int i = 0; i < length; ++i)
		fprintf(outputFile, "%f %f\n", i * dt, vector[i]);

	close(outputFile);
}

void outputDoubles(const char *filePath, const double *vector1, const double *vector2, size_t length)
{
	FILE *outputFile = file(filePath, "wt");

	for(int i = 0; i < length; ++i)
		fprintf(outputFile, "%f %f %f\n", i * dt, vector1[i], vector2[i]);

	close(outputFile);
}
