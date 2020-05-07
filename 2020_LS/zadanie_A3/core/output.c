//
// Created by xgallom on 3/18/20.
//

#include "output.h"
#include "file.h"
#include "../constants.h"

#define OUTPUT_STRING(length, format) ((length) ? format " " : format "\n")
#define DOUBLE_OUTPUT_STRING(length) OUTPUT_STRING(length, "%f")
#define STRING_OUTPUT_STRING(length) OUTPUT_STRING(length, "%s")

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

void outputStatistics(FILE *outputFile, const char *index, const double *vector, size_t length)
{
	fprintf(outputFile, STRING_OUTPUT_STRING(length), index);
	while(length--)
		fprintf(outputFile, DOUBLE_OUTPUT_STRING(length), *vector++);
}
