//
// Created by xgallom on 3/18/20.
//

#include "parse.h"
#include "error.h"

#include <stdlib.h>
#include <errno.h>

double parseDouble(const char *string)
{
	char *end = NULL;

	const double result = strtod(string, &end);

	fail(end == string || errno == ERANGE, "Failed converting \"%s\" to double\n", string);

	return result;
}
