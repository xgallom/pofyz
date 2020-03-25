#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"

int main(int argc, char *argv[])
{
	initializeRootPath(argc, argv);
	struct Arguments arguments = parseArguments(argc, argv);
	dumpArguments(&arguments);

	initializeTemperature(&arguments);

	dumpTemperature();

	cleanupTemperature();
	cleanupRootPath();

	return 0;
}
