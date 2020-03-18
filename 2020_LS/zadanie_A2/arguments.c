//
// Created by xgallom on 3/18/20.
//

#include "arguments.h"
#include "core/error.h"
#include "core/toStr.h"
#include "core/exit.h"
#include "core/parse.h"

#include <stdio.h>
#include <string.h>

#define EXPECTED_ARGUMENTS 1
#define EXPECTED_ARGC (1 + EXPECTED_ARGUMENTS)

#define PROGRAM_NAME_INDEX 0
#define X_0_INDEX 1

static void printUsage(const char *programName)
{
	printf(
			"Usage:\n"
			"  %s x_0\n"
			"    executes program with parameters:\n"
			"      x_0: <double> - Initial height of fall\n\n"

			"  %s <-h|--help>\n"
			"    prints this usage\n\n",

			programName,
			programName
	);
}

Arguments parseArguments(int argc, char *argv[])
{
	const char *const programName = argv[PROGRAM_NAME_INDEX];

	if(argc != EXPECTED_ARGC) {
		error("Wrong number of arguments supplied, expected " TO_STR(EXPECTED_ARGUMENTS) "\n\n");
		printUsage(programName);
		exitFailure();
	}

	const char *const argument = argv[X_0_INDEX];

	if(strcmp(argument, "--help") == 0 || strcmp(argument, "-h") == 0) {
		printUsage(programName);
		exitSuccess();
	}

	Arguments result = {
			.x_0 =  parseDouble(argument)
	};

	return result;
}
