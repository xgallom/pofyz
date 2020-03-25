//
// Created by xgallom on 3/25/20.
//

#include "rootPath.h"
#include "error.h"

#include <string.h>

#ifndef ROOT_PATH
#include <libgen.h>
#endif

static struct Vector path = NULL_VECTOR;

void initializeRootPath(int argc, char *argv[])
{
	fail(!isNull(&path), "Root path initialized multiple times\n");

#ifdef ROOT_PATH
	path = stringFrom(ROOT_PATH);
#else
	fail(argc <= PROGRAM_NAME_INDEX, "Invalid function arguments supplied to main\n");

	struct Vector programPath = stringFrom(argv[PROGRAM_NAME_INDEX]);

	path = stringFrom(dirname(asString(&programPath)));

	delete(&programPath);
#endif
}

const char *rootPath(void)
{
	return asCString(&path);
}

struct Vector pathFor(const char *relativePath)
{
	const size_t length = strlen(relativePath);

	struct Vector result = string(path.length + length);
	strncpy(asString(&result), asCString(&path), path.length);
	strncpy(asString(&result) + path.length, relativePath, length);

	return result;
}
