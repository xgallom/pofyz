#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"
#include "solvers/simulation/rungeKutta.h"
#include "constants.h"
#include "solvers/simulation/statistics.h"
#include "core/output.h"
#include "core/exit.h"
#include "core/file.h"

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

	struct Vector
			x = vectorDouble(BATCH_SIZE),
			v = vectorDouble(BATCH_SIZE);

	const size_t length = solveRungeKutta(&x, &v);

	printf("\nSimulation took %zu steps\n", length);


	printf("\nWriting simulation to file\n\n");

	outputDoubles("runge_kutta.txt", asCDouble(&x), asCDouble(&v), length);


	printf("\nComputing statistics\n\n");

	const struct Statistics statistics = constructStatistics(asCDouble(&x), asCDouble(&v), length);


	printf("\nWriting statistics to file\n\n");

	FILE *statisticsFile = file("statistics.txt", "at");
	outputStatistics(statisticsFile, asCString(&arguments.stringOption.name), statistics.statistics, STATISTIC_COUNT);
	close(statisticsFile);


	printf("\nClean up\n\n");

	delete(&x);
	delete(&v);

	cleanupTemperature();
	cleanupRootPath();


	printf("\nFinished\n\n");

	return Success();
}
