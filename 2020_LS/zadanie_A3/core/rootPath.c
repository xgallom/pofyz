//
// Created by xgallom on 3/25/20.
//

#include "rootPath.h"
#include "error.h"

#include <stdio.h>
#include <string.h>

#if defined(USE_STATIC_ROOT_PATH) && defined(ROOT_PATH)
#define HAS_STATIC_ROOT_PATH 1
#else
#define HAS_STATIC_ROOT_PATH 0
#endif

#if !HAS_STATIC_ROOT_PATH

#include <libgen.h>

#endif

static struct Vector path = NULL_VECTOR;

void initializeRootPath(int argc, char *argv[])
{
	fail(!isNull(&path), "Root path initialized multiple times\n");

#if HAS_STATIC_ROOT_PATH
	path = stringView(ROOT_PATH);
#else
	fail(argc <= PROGRAM_NAME_INDEX, "Invalid function arguments supplied to main\n");
	struct Vector programPath = stringFrom(argv[PROGRAM_NAME_INDEX]);

	path = stringFrom(dirname(asString(&programPath)));

	delete(&programPath);
#endif

	printf("Resolved root path to \"%s\"\n\n", rootPath());
}

void cleanupRootPath(void)
{
#if !HAS_STATIC_ROOT_PATH
	delete(&path);
#endif
}

const char *rootPath(void)
{
	return asCString(&path);
}

struct Vector pathFor(const char *relativePath)
{
	const size_t
			length = strlen(relativePath),
			pathLength = strlen(asCString(&path));

	struct Vector result = string(pathLength + length);

	strcpy(asString(&result), asCString(&path));
	strcpy(asString(&result) + pathLength, relativePath);

	return result;
}
