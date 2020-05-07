//
// Created by xgallom on 5/7/20.
//

#include "arguments.h"
#include "tables/parameterTables.h"
#include "tables/intOptionTables.h"
#include "tables/stringOptionTables.h"

#include <stdio.h>

static void dumpParameters(const struct Arguments *arguments)
{
	for(int i = 0; i < PARAMETER_COUNT; ++i) {
		const char *unit = ParametersDetailsTable[i][PARAMETERS_DETAILS_UNIT];

		printf(
				"    %16s = %8.2f %s\n",
				ParametersTable[i],
				arguments->parameters[i],
				unit ? unit : ""
		);
	}
}

static void dumpIntOptions(const struct Arguments *arguments)
{
	for(int i = 0; i < INTOPTION_COUNT; ++i) {
		printf(
				"    %16s : %d\n",
				IntOptionsTable[i],
				arguments->intOptions[i]
		);
	}
}

static void dumpStringOptions(const struct Arguments *arguments)
{
	for(int i = 0; i < STRINGOPTION_COUNT; ++i) {
		const char *stringOption = asCString(arguments->stringOptions + i);

		if(stringOption)
			printf(
					"    %16s : \"%s\"\n",
					StringOptionsTable[i],
					stringOption
			);
		else
			printf("    %16s : <default>\n", StringOptionsTable[i]);
	}
}

void dumpArguments(const struct Arguments *arguments)
{
	printf("Simulating with parameters:\n");
	dumpParameters(arguments);

	printf("\nSimulating with options:\n");
	dumpIntOptions(arguments);
	dumpStringOptions(arguments);

	printf("\n");
}
