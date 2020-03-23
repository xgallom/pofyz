#include "core/vector.h"
#include "core/file.h"
#include "core/output.h"
#include "constants.h"
#include "solvers/rungeKutta.h"
#include "solvers/statistics.h"

#define T_MIN    -60.0
#define T_MAX    50.0
#define T_STEP   10.0
#define ITERS    ((T_MAX - T_MIN) / T_STEP)
#define T_FOR(i) (T_MIN + T_STEP * (i) + 273.15)

int main(int argc, char *argv[])
{
	struct Arguments arguments = parseArguments(argc, argv);
	arguments.parameter.x_0 = 4000.0;

	dumpParameters(&arguments);

	struct Vector
			x = vectorDouble(steps),
			v = vectorDouble(steps);

	FILE *outputFile = file("statistics.txt", "wt");

	for(int i = 0; i <= ITERS; ++i) {
		const double temperature = T_FOR(i);

		arguments.parameter.T = temperature;
		initializeConstants(arguments);

		size_t length = solveRungeKutta(&x, &v);
		printf("Runge Kutta solution for T=%f: %zu\n", temperature, length);

		struct Statistics statistics = constructStatistics(asCDouble(&x), asCDouble(&v), length);
		outputRow(outputFile, temperature, statistics.statistics, STATISTIC_COUNT);
	}

	close(outputFile);

	delete(&x);
	delete(&v);

	return 0;
}
