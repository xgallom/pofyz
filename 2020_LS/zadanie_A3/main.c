#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"

int main(int argc, char *argv[])
{
	struct Arguments arguments = parseArguments(argc, argv);
	dumpArguments(&arguments);

	initializeRootPath(argc, argv);
	initializeTemperature(&arguments);

	dumpTemperature();

	cleanupTemperature();
	cleanupRootPath();

	return 0;
}
