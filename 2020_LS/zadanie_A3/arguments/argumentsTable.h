//
// Created by xgallom on 3/25/20.
//

#ifndef POFYZ_2020_LS_ZADANIE_A3_ARGUMENTS_ARGUMENTSTABLE_H
#define POFYZ_2020_LS_ZADANIE_A3_ARGUMENTS_ARGUMENTSTABLE_H

#include <stddef.h>

#define ARGUMENTS_TABLE_PARAMETERS 0
#define ARGUMENTS_TABLE_DATAFILES  1

#define ARGUMENT_INVALID -1
#define ARGUMENTS_TABLE_COUNT      2

struct Arguments;

typedef void (ArgumentParser) (void *result, const char *argument);

struct ArgumentTable {
	const char **keysTable;
	size_t keysCount;
	ArgumentParser *parser;
	size_t argumentEntryOffset;
	size_t argumentEntrySize;
};

extern const struct ArgumentTable ArgumentsTable[ARGUMENTS_TABLE_COUNT];
void *entryFor(const struct ArgumentTable *argumentTable, struct Arguments *arguments, size_t index);

#endif //POFYZ_2020_LS_ZADANIE_A3_ARGUMENTS_ARGUMENTSTABLE_H
