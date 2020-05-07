//
// Created by xgallom on 3/25/20.
//

#include "argumentsTable.h"
#include "arguments.h"
#include "parameterTables.h"
#include "intOptionTables.h"
#include "stringOptionTables.h"
#include "../core/parse.h"
#include "../core/vector.h"

static void parseDoubleArgument(double *result, const char *argument)
{
	*result = parseDouble(argument);
}

static void parseIntArgument(int *result, const char *argument)
{
	*result = parseInt(argument);
}

static void parseStringArgument(struct Vector *result, const char *argument)
{
	if(!isNull(result))
		delete(result);

	*result = stringFrom(argument);
}

const struct ArgumentTable ArgumentsTable[ARGUMENTS_TABLE_COUNT] = {
		[ARGUMENTS_TABLE_PARAMETERS] = {
				.keysTable = ParametersTable,
				.keysCount = PARAMETER_COUNT,
				.parser = (ArgumentParser *) &parseDoubleArgument,
				.argumentEntryOffset = offsetof(struct Arguments, parameters),
				.argumentEntrySize = sizeof(double)
		},
		[ARGUMENTS_TABLE_INTOPTIONS] = {
				.keysTable = IntOptionsTable,
				.keysCount = INTOPTION_COUNT,
				.parser = (ArgumentParser *) &parseIntArgument,
				.argumentEntryOffset = offsetof(struct Arguments, intOptions),
				.argumentEntrySize = sizeof(int)
		},
		[ARGUMENTS_TABLE_STRINGOPTIONS] = {
				.keysTable = StringOptionsTable,
				.keysCount = STRINGOPTION_COUNT,
				.parser = (ArgumentParser *) &parseStringArgument,
				.argumentEntryOffset = offsetof(struct Arguments, stringOptions),
				.argumentEntrySize = sizeof(struct Vector)
		}
};

void *entryFor(const struct ArgumentTable *argumentTable, struct Arguments *arguments, size_t index)
{
	uint8_t *base = (uint8_t *) arguments;
	return
			base +
			argumentTable->argumentEntryOffset +
			index * argumentTable->argumentEntrySize;
}
