//
// Created by xgallom on 3/18/20.
//

#include "arguments.h"
#include "parameterTables.h"
#include "dataFileTables.h"
#include "argumentsTable.h"
#include "../core/error.h"
#include "../core/toStr.h"
#include "../core/exit.h"
#include "../core/parse.h"
#include "../core/rootPath.h"

#include <stdio.h>
#include <string.h>

#define FIRST_ARGUMENT 1
#define MINIMUM_ARGUMENTS 0
#define MINIMUM_ARGC (FIRST_ARGUMENT + MINIMUM_ARGUMENTS)

#define HELP_ARGUMENT "--help"
#define DASH_CHARACTER '-'
#define SPLIT_CHARACTER '='

static void printUsage(const char *programName)
{
	printf(
			"Usage:\n"
			"  %s [--{parameter}={value} ...] [--{data_file}={value} ...]\n",
			programName
	);

	printf("  executes program with custom parameters:\n");
	char unitRepresentation[6] = {};
	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		const char *unit = ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT];
		snprintf(unitRepresentation, 6, "[%s]", unit ? unit : "-");
		printf(
				"    %10s %-5s - %s\n",
				ParametersTable[i],
				unitRepresentation,
				ParametersDetailsTable[i][PARAMETERS_DETAILS_DESC]
		);
	}

	printf("\n  executes program with custom data files:\n");
	for(int i = 0; i < DATAFILE_COUNT; ++i)
		printf(
				"    %16s - %s\n",
				DataFilesTable[i],
				DataFilesDetailsTable[i][DATAFILES_DETAILS_DESC]
				);

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

static int findIndex(const char *key, const char *keysTable[], size_t keysCount)
{
	for(int index = 0; index < keysCount; ++index) {
		if(strcmp(key, keysTable[index]) == 0)
			return index;
	}

	return ARGUMENT_INVALID;
}

static void parseArgumentKeyValue(
		struct Arguments *arguments,
		int index,
		const char *key,
		const char *value,
		const char *programName)
{
	for(int tableIndex = 0; tableIndex < ARGUMENTS_TABLE_COUNT; ++tableIndex) {
		const struct ArgumentTable *const argumentTable = ArgumentsTable + tableIndex;

		int keyIndex = findIndex(key, argumentTable->keysTable, argumentTable->keysCount);

		if(keyIndex != ARGUMENT_INVALID) {
			(*argumentTable->parser)(entryFor(argumentTable, arguments, keyIndex), value);
			return;
		}
	}

	invalidArgument(1, index, key, programName);
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
	parseArgumentKeyValue(arguments, index, argument, valueStart, programName);
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
			},
			.dataFile = {
					.temperature = NULL_VECTOR,
			}
	};

	if(argc < MINIMUM_ARGC) {
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
				length < 3 ||
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
	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		const char *unit = ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT];

		printf(
				"%4s = %8.2f %s\n",
				ParametersTable[i],
				arguments->parameters[i],
				unit ? unit : ""
		);
	}
	printf("\n\n");
}
