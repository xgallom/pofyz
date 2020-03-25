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

size_t lineCount(FILE *file)
{
	const fpos_t oldPosition = filePosition(file);

	fail(fseek(file, 0, SEEK_SET) != 0, "Failed to set file position\n");

	size_t lines = 0;
	for(int c = 0; (c = fgetc(file)) != EOF;)
		lines += c == '\n' ? 1 : 0;

	setFilePosition(file, &oldPosition);

	return lines;
}

fpos_t filePosition(FILE *file)
{
	fpos_t position;

	fail(fgetpos(file, &position) != 0, "Failed to get current file position\n");

	return position;
}

void setFilePosition(FILE *file, const fpos_t *position)
{
	fail(fsetpos(file, position) != 0, "Failed to set file position\n");
}
