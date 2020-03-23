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

#define FIRST_ARGUMENT 1
#define MINIMUM_ARGUMENTS 0
#define MAXIMUM_ARGUMENTS PARAMETER_COUNT
#define MINIMUM_ARGC (FIRST_ARGUMENT + MINIMUM_ARGUMENTS)
#define MAXIMUM_ARGC (FIRST_ARGUMENT + MAXIMUM_ARGUMENTS)

#define PROGRAM_NAME_INDEX 0

#define HELP_ARGUMENT "--help"
#define DASH_CHARACTER '-'
#define SPLIT_CHARACTER '='

static const char *ParametersTable[PARAMETER_COUNT] = {
		// SIMULATION PARAMETERS
		"x_0",
		"v_0",
		"dt",

		// OBJECT PARAMETERS
		"m",
		"S",
		"C",
		"T"
};

static const char *ParametersDetailsTable[PARAMETER_COUNT][2] = {
		{"m",   "[up] Initial height of fall"},
		{"m/s", "[up] Initial fall velocity"},
		{"s",   "Time step of simulation"},

		{"kg",  "Mass of falling object"},
		{"m2",  "Effective area of falling object"},
		{"-",   "Drag coefficient"},
		{"K",   "Temperature of air"}
};

#define PARAMETERS_DETAILS_UNIT 0
#define PARAMETERS_DETAILS_DESC 1

static void printUsage(const char *programName)
{
	printf(
			"Usage:\n"
			"  %s [--{parameter}={value} ...]\n"
			"    executes program with custom parameters:\n",
			programName
	);

	char unit[5] = {};

	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		sprintf(unit, "[%s]", ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT]);
		printf(
				"    %4s %5s: %s\n",
				ParametersTable[i],
				unit,
				ParametersDetailsTable[i][PARAMETERS_DETAILS_DESC]
		);
	}

	printf("\n"
		   "  %s " HELP_ARGUMENT "\n"
		   "    prints this usage\n"
		   "\n",
		   programName
	);
}

static inline void invalidArgument(int check, int index, const char *argument, const char *programName)
{
	if(check) {
		error("Invalid argument %d: Error in \"%s\"\n\n", index, argument);
		printUsage(programName);
		exitFailure();
	}
}

static int findIndex(const char *key)
{
	for(int index = 0; index < PARAMETER_COUNT; ++index) {
		if(strcmp(key, ParametersTable[index]) == 0)
			return index;
	}

	return PARAMETER_INVALID;
}

static void parseArgument(
		struct Arguments *arguments,
		int index,
		char *argument,
		const char *argumentEnd,
		const char *programName)
{
	char *keyEnd = argument;

	while(*++keyEnd != SPLIT_CHARACTER)
		invalidArgument(keyEnd >= argumentEnd, index, argument, programName);

	const char *const valueStart = keyEnd + 1;

	invalidArgument(valueStart >= argumentEnd, index, argument, programName);

	*keyEnd = '\0';
	int parameterIndex = findIndex(argument);

	invalidArgument(parameterIndex == PARAMETER_INVALID, index, argument, programName);

	arguments->parameters[parameterIndex] = parseDouble(valueStart);
}

struct Arguments parseArguments(int argc, char *argv[])
{
	const char *const programName = argv[PROGRAM_NAME_INDEX];

	struct Arguments arguments = {
			.parameter = {
					// SIMULATION PARAMETERS
					.x_0 = 80.0,
					.v_0 = 0.0,
					.dt = 0.01,

					// OBJECT PARAMETERS
					.m = 80.0,
					.S = 0.2,
					.C = 0.8,
					.T = 293.15
			}
	};

	if(argc < MINIMUM_ARGC || argc > MAXIMUM_ARGC) {
		error(
				"Wrong number of arguments supplied, expected between "
				TO_STR(MINIMUM_ARGC)
				" and "
				TO_STR(MAXIMUM_ARGC)
				"\n\n"
		);
		printUsage(programName);
		exitFailure();
	}

	for(int i = FIRST_ARGUMENT; i < argc; ++i) {
		char *const argument = argv[i];
		const size_t length = strlen(argument);

		if(strcmp(argument, HELP_ARGUMENT) == 0) {
			printUsage(programName);
			exitSuccess();
		}

		invalidArgument(
				length < 2 ||
				argument[0] != DASH_CHARACTER ||
				argument[1] != DASH_CHARACTER,
				i, argument, programName
		);
		parseArgument(&arguments, i, argument + 2, argument + length, programName);
	}

	return arguments;
}

void dumpParameters(const struct Arguments *arguments)
{
	printf("Simulating with parameters:\n");
	for(int i = 0; i < PARAMETER_COUNT; ++i)
		printf(
				"%4s = %8g %s\n",
				ParametersTable[i],
				arguments->parameters[i],
				ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT]
		);
	printf("\n\n");
}
