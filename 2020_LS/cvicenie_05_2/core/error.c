//
// Created by xgallom on 3/18/20.
//

#include "error.h"
#include "exit.h"

#include <stdio.h>
#include <stdarg.h>

void error(const char *message, ...)
{
	va_list args;

	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
}

void die(const char *message, ...)
{
	va_list args;

	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);

	exitFailure();
}

void fail(int check, const char *message, ...)
{
	if(check) {
		va_list args;

		va_start(args, message);
		vfprintf(stderr, message, args);
		va_end(args);

		exitFailure();
	}
}
