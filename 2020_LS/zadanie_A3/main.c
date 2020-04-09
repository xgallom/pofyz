#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"
#include "core/matrix.h"
#include "solvers/linearLeastSquares.h"
#include "equations/polynomial.h"

#include <stdio.h>

#define SEPARATOR for(size_t _n = 0; _n < 80; ++_n) putchar('-');

int main(int argc, char *argv[])
{
	struct Arguments arguments = parseArguments(argc, argv);
	dumpArguments(&arguments);

	initializeRootPath(argc, argv);
	initializeTemperature(&arguments);

	dumpTemperature();

	SEPARATOR
	printf("\nLinearne fitovanie:\n\n");
	struct Matrix coefficients = solveLinearLeastSquares(temperaturePositions(), temperatureValues(), 5);

	SEPARATOR
	printf("\nOverenie fungovania funkcie computePolynomial s koeficientami pre teplotu (Tfun):\n\n");
	for(double x = 0.0; x <= 80e3; x += 2500.0)
		printf("T(%4.1f km) = %f K\n", x / 1000.0, computePolynomial(x, &coefficients));

	cleanupTemperature();
	cleanupRootPath();

	return 0;
}
