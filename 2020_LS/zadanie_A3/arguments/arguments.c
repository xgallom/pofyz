//
// Created by xgallom on 3/18/20.
//

#include "arguments.h"
#include "parameterTables.h"
#include "optionTables.h"
#include "dataFileTables.h"
#include "argumentsTable.h"
#include "../core/error.h"
#include "../core/exit.h"
#include "../core/rootPath.h"

#include <stdio.h>
#include <string.h>

#define FIRST_ARGUMENT 1

#define HELP_ARGUMENT "--help"
#define DASH_CHARACTER '-'
#define SPLIT_CHARACTER '='
#define MAX_WIDTH 80

static void printUsage()
{
	char buffer[BUFSIZ];
	sprintf(buffer, "Usage: " PROGRAM_NAME);
	printf("%s", buffer);

	const size_t offsetStart = strlen(buffer);
	size_t currentLength = offsetStart;

	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		sprintf(buffer, " [--%s={double}]", ParametersTable[i]);
		const size_t length = strlen(buffer);

		if(currentLength + length > MAX_WIDTH) {
			printf("\n%*c", (int) offsetStart, ' ');
			currentLength = offsetStart;
		}

		printf("%s", buffer);
		currentLength += length;
	}
	for(int i = 0; i < OPTION_COUNT; ++i) {
		sprintf(buffer, " [--%s={int}]", OptionsTable[i]);
		const size_t length = strlen(buffer);

		if(currentLength + length > MAX_WIDTH) {
			printf("\n%*c", (int) offsetStart, ' ');
			currentLength = offsetStart;
		}

		printf("%s", buffer);
		currentLength += length;
	}
	for(int i = 0; i < DATAFILE_COUNT; ++i) {
		sprintf(buffer, " [--%s={path}]", DataFilesTable[i]);
		const size_t length = strlen(buffer);

		if(currentLength + length > MAX_WIDTH) {
			printf("\n%*c", (int) offsetStart, ' ');
			currentLength = offsetStart;
		}

		printf("%s", buffer);
		currentLength += length;
	}

	sprintf(buffer, " [" HELP_ARGUMENT "]");
	const size_t length = strlen(buffer);
	if(currentLength + length > MAX_WIDTH)
		printf("\n%*c", (int) offsetStart, ' ');
	printf("%s\n\n", buffer);

	printf("  Executes program with custom parameters:\n");
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

	printf("\n  Executes program with custom options:\n");
	for(int i = 0; i < OPTION_COUNT; ++i)
		printf(
				"    %16s - %s\n",
				OptionsTable[i],
				OptionsDetailsTable[i][DATAFILES_DETAILS_DESC]
		);

	printf("\n  Executes program with custom data files:\n");
	for(int i = 0; i < DATAFILE_COUNT; ++i)
		printf(
				"    %16s - %s\n",
				DataFilesTable[i],
				DataFilesDetailsTable[i][DATAFILES_DETAILS_DESC]
		);

	printf("\n  Executes program with flags:\n"
		   "    %16s - %s\n"
		   "\n",
		   HELP_ARGUMENT,
		   "Prints this usage"
	);
}

static inline void invalidArgument(int check, int index, const char *argument)
{
	if(check) {
		error("Invalid argument %d: Error in \"%s\"\n\n", index, argument);
		printUsage();
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
		const char *value)
{
	for(int tableIndex = 0; tableIndex < ARGUMENTS_TABLE_COUNT; ++tableIndex) {
		const struct ArgumentTable *const argumentTable = ArgumentsTable + tableIndex;

		int keyIndex = findIndex(key, argumentTable->keysTable, argumentTable->keysCount);

		if(keyIndex != ARGUMENT_INVALID) {
			(*argumentTable->parser)(entryFor(argumentTable, arguments, keyIndex), value);
			return;
		}
	}

	invalidArgument(1, index, key);
}

static void parseArgument(
		struct Arguments *arguments,
		int index,
		char *argument,
		const char *argumentEnd)
{
	char *keyEnd = argument;

	while(*++keyEnd != SPLIT_CHARACTER)
		invalidArgument(keyEnd >= argumentEnd, index, argument);

	const char *const valueStart = keyEnd + 1;

	invalidArgument(valueStart >= argumentEnd, index, argument);

	*keyEnd = '\0';
	parseArgumentKeyValue(arguments, index, argument, valueStart);
}

struct Arguments parseArguments(int argc, char *argv[])
{
	struct Arguments arguments = {
			.parameter = {
					// SIMULATION PARAMETERS
					.x_0 = 31300.0,
					.v_0 = 0.0,
					.dt = 0.01,

					// OBJECT PARAMETERS
					.m = 80.0,
					.x_open = 0.0,
					.x_max = 200.0,
					.S_0 = 0.2,
					.S_max = 32.0,
					.C_0 = 0.8,
					.C_max = 1.75,
			},
			.option = {
					.polynomialDegree = 5,
			},
			.dataFile = {
					.temperature = NULL_VECTOR,
			}
	};

	for(int i = FIRST_ARGUMENT; i < argc; ++i) {
		char *const argument = argv[i];
		const size_t length = strlen(argument);

		if(strcmp(argument, HELP_ARGUMENT) == 0) {
			printUsage();
			exitSuccess();
		}

		invalidArgument(
				length < 3 ||
				argument[0] != DASH_CHARACTER ||
				argument[1] != DASH_CHARACTER,
				i, argument
		);
		parseArgument(&arguments, i, argument + 2, argument + length);
	}

	return arguments;
}

void dumpArguments(const struct Arguments *arguments)
{
	printf("Simulating with parameters:\n");
	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		const char *unit = ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT];

		printf(
				"    %16s = %8.2f %s\n",
				ParametersTable[i],
				arguments->parameters[i],
				unit ? unit : ""
		);
	}

	printf("\nSimulating with options:\n");
	for(int i = 0; i < OPTION_COUNT; ++i) {
		printf(
				"    %16s : %d\n",
				OptionsTable[i],
				arguments->options[i]
		);
	}

	printf("\nSimulating with dataFiles:\n");
	for(int i = 0; i < DATAFILE_COUNT; ++i) {
		const char *dataFile = asCString(arguments->dataFiles + i);

		if(dataFile)
			printf(
					"    %16s : \"%s\"\n",
					DataFilesTable[i],
					dataFile
			);
		else
			printf("    %16s : <default>\n", DataFilesTable[i]);
	}

	printf("\n");
}
