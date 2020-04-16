//
// Created by xgallom on 3/25/20.
//

#include "argumentsTable.h"
#include "arguments.h"
#include "parameterTables.h"
#include "optionTables.h"
#include "dataFileTables.h"
#include "../core/parse.h"
#include "../core/vector.h"

static void parseParameter(double *result, const char *argument)
{
	*result = parseDouble(argument);
}

static void parseOption(int *result, const char *argument)
{
	*result = parseInt(argument);
}

static void parseDataFile(struct Vector *result, const char *argument)
{
	if(!isNull(result))
		delete(result);

	*result = stringFrom(argument);
}

const struct ArgumentTable ArgumentsTable[ARGUMENTS_TABLE_COUNT] = {
		[ARGUMENTS_TABLE_PARAMETERS] = {
				.keysTable = ParametersTable,
				.keysCount = PARAMETER_COUNT,
				.parser = (ArgumentParser *) &parseParameter,
				.argumentEntryOffset = offsetof(struct Arguments, parameters),
				.argumentEntrySize = sizeof(double)
		},
		[ARGUMENTS_TABLE_OPTIONS] = {
				.keysTable = OptionsTable,
				.keysCount = OPTION_COUNT,
				.parser = (ArgumentParser *) &parseOption,
				.argumentEntryOffset = offsetof(struct Arguments, options),
				.argumentEntrySize = sizeof(int)
		},
		[ARGUMENTS_TABLE_DATAFILES] = {
				.keysTable = DataFilesTable,
				.keysCount = DATAFILE_COUNT,
				.parser = (ArgumentParser *) &parseDataFile,
				.argumentEntryOffset = offsetof(struct Arguments, dataFiles),
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
