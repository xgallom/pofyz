#include "data/temperature.h"

int main(int argc, char *argv[])
{
	initializeTemperature();

	dumpTemperature();

	cleanupTemperature();

	return 0;
}
