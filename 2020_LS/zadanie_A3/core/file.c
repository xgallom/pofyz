//
// Created by xgallom on 3/18/20.
//

#include "file.h"
#include "error.h"

FILE *file(const char *filePath, const char *flags)
{
	FILE *result = fopen(filePath, flags);

	fail(result == NULL, "Failed to open file \"%s\"\n", filePath);

	return result;
}

void close(FILE *file)
{
	fail(fclose(file) != 0, "Failed to close file\n");
}
