#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"
#include "solvers/rungeKutta.h"
#include "constants.h"
#include "core/output.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	const struct Arguments arguments = parseArguments(argc, argv);
	dumpArguments(&arguments);

	printf("\nInitializing\n\n");
	initializeRootPath(argc, argv);
	initializeTemperature(&arguments);
	initializeConstants(&arguments);

	dumpTemperature();

	printf("\nSimulating\n\n");

	struct Vector x = vectorDouble(batchSize), v = vectorDouble(batchSize);
	const size_t length = solveRungeKutta(&x, &v);

	printf("\nSimulation took %zu steps\n", length);

	printf("\nWriting to file\n\n");

	outputDoubles("runge_kutta.txt", asCDouble(&x), asCDouble(&v), length);

	printf("\nClean up\n\n");

	cleanupTemperature();
	cleanupRootPath();

	return 0;
}
