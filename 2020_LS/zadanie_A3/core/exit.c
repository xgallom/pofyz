//
// Created by xgallom on 3/18/20.
//

#include "exit.h"

#include <stdlib.h>

int Success(void)
{
	return EXIT_SUCCESS;
}

void exitSuccess(void)
{
	exit(EXIT_SUCCESS);
}

void exitFailure(void)
{
	exit(EXIT_FAILURE);
}
