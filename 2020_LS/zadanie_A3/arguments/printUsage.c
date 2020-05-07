//
// Created by xgallom on 5/7/20.
//

#include "printUsage.h"
#include "arguments.h"
#include "tables/parameterTables.h"
#include "tables/intOptionTables.h"
#include "tables/stringOptionTables.h"
#include "../core/rootPath.h"

#include <stdio.h>
#include <string.h>

#define MAX_WIDTH 80

static inline void printBuffer(const char *buffer, size_t length, size_t *currentLength, size_t offsetStart)
{
	if(*currentLength + length > MAX_WIDTH) {
		printf("\n%*c", (int) offsetStart, ' ');
		*currentLength = offsetStart;
	}

	printf("%s", buffer);
	*currentLength += length;
}

static void printUsageInfo(void)
{
	char buffer[BUFSIZ];
	sprintf(buffer, "Usage: " PROGRAM_NAME);
	printf("%s", buffer);

	const size_t offsetStart = strlen(buffer);
	size_t currentLength = offsetStart;

	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		sprintf(buffer, " [--%s={double}]", ParametersTable[i]);
		printBuffer(buffer, strlen(buffer), &currentLength, offsetStart);
	}

	for(int i = 0; i < INTOPTION_COUNT; ++i) {
		sprintf(buffer, " [--%s={int}]", IntOptionsTable[i]);
		printBuffer(buffer, strlen(buffer), &currentLength, offsetStart);
	}

	for(int i = 0; i < STRINGOPTION_COUNT; ++i) {
		sprintf(buffer, " [--%s={string}]", StringOptionsTable[i]);
		printBuffer(buffer, strlen(buffer), &currentLength, offsetStart);
	}

	sprintf(buffer, " [" HELP_ARGUMENT "]");
	printBuffer(buffer, strlen(buffer), &currentLength, offsetStart);
	printf("\n\n");
}

static void printParameterDescriptions(void)
{
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
}

static void printIntOptionDescriptions(void)
{
	for(int i = 0; i < INTOPTION_COUNT; ++i) {
		printf(
				"    %16s - %s\n",
				IntOptionsTable[i],
				IntOptionsDetailsTable[i][INTOPTIONS_DETAILS_DESC]
		);
	}
}

static void printStringOptionDescriptions(void)
{
	for(int i = 0; i < STRINGOPTION_COUNT; ++i) {
		printf(
				"    %16s - %s\n",
				StringOptionsTable[i],
				StringOptionsDetailsTable[i][STRINGOPTIONS_DETAILS_DESC]
		);
	}
}

static void printUsageDescription(void)
{
	printf("  Executes program with custom parameters:\n");
	printParameterDescriptions();

	printf("\n  Executes program with custom options:\n");
	printIntOptionDescriptions();
	printStringOptionDescriptions();

	printf("\n  Executes program with flags:\n"
		   "    %16s - %s\n"
		   "\n",
		   HELP_ARGUMENT,
		   "Prints this usage"
	);
}

void printUsage(void)
{
	printUsageInfo();
	printUsageDescription();
}
