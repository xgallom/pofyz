//
// Created by xgallom on 3/18/20.
//

#include "output.h"
#include "file.h"
#include "../constants.h"

#define DOUBLE_OUTPUT_STRING(length) ((length) ? "%f " : "%f\n")

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

void outputRow(FILE *outputFile, double index, const double *vector, size_t length)
{
	fprintf(outputFile, DOUBLE_OUTPUT_STRING(length), index);
	while(length--)
		fprintf(outputFile, DOUBLE_OUTPUT_STRING(length), *vector++);
}
