//
// Created by xgallom on 3/18/20.
//

#include "arguments.h"
#include "tables/argumentsTable.h"
#include "../core/error.h"
#include "../core/exit.h"
#include "printUsage.h"

#include <string.h>

#define FIRST_ARGUMENT 1

#define DASH_CHARACTER '-'
#define SPLIT_CHARACTER '='

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
			.intOption = {
					.polynomialDegree = 5,
			},
			.stringOption = {
					.temperature = NULL_VECTOR,
					.name = stringFrom("untitled"),
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

