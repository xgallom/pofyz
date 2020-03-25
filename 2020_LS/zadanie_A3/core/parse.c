//
// Created by xgallom on 3/18/20.
//

#include "parse.h"
#include "error.h"

#include <stdlib.h>
#include <errno.h>

double parseDouble(const char *string)
{
	double result;

	fail(parseDoubles(string, &result, 1) != 1, "Failed converting \"%s\" to double\n", string);

	return result;
}

size_t parseDoubles(const char *string, double *buffer, size_t count)
{
	const size_t total = count;
	char *end = NULL;

	for(count = 0; count < total; ++count) {
		*buffer++ = strtod(string, &end);

		if(end == string || errno == ERANGE)
			break;

		string = end;
	}

	return count;
}
