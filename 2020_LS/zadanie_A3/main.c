#include "core/rootPath.h"
#include "data/temperature.h"

int main(int argc, char *argv[])
{
	initializeRootPath(argc, argv);
	initializeTemperature();

	dumpTemperature();

	cleanupTemperature();

	return 0;
}
