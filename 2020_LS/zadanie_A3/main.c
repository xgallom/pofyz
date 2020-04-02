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
	printf("\nKoeficienty este nie su vyratane, preto som ich naplnil postupne klesajucimi hodnotami:\n\n");
	double *coefficient = asMDouble(&coefficients);
	for(size_t i = 0; i < coefficients.length; ++i)
		*coefficient++ = ((double) coefficients.length - i) / coefficients.length;
	dumpMatrix(&coefficients);

	SEPARATOR
	printf("\nOverenie fungovania funkcie computePolynomial s nedoratanymi koeficientami pre teplotu (Tfun):\n\n");
	for(double x = 0.0; x < 10.0; x += 0.5) {
		printf("T(%4.1lf) = ", x);

		coefficient = asMDouble(&coefficients);
		for(size_t n = 0; n < coefficients.length; ++n)
			printf("%s %g %3.1f^%d ", n ? "+" : "", *coefficient++, x, n);

		printf("\n        = %f\n\n", computePolynomial(x, &coefficients));
	}

	cleanupTemperature();
	cleanupRootPath();

	return 0;
}
