#include "core/rootPath.h"
#include "arguments/arguments.h"
#include "data/temperature.h"
#include "core/matrix.h"
#include "core/file.h"
#include "core/output.h"
#include "solvers/linearLeastSquares.h"
#include "equations/polynomial.h"
#include "equations/general.h"

#include <stdio.h>

#define SEPARATOR for(size_t _n = 0; _n < 80; ++_n) putchar('-');

int main(int argc, char *argv[])
{
	const struct Arguments arguments = parseArguments(argc, argv);
	dumpArguments(&arguments);

	initializeRootPath(argc, argv);
	initializeTemperature(&arguments);

	dumpTemperature();

	const struct Matrix *positions = temperaturePositions();


	SEPARATOR
	printf("\nLinearne fitovanie\n\n");

	struct Matrix coefficients = solveLinearLeastSquares(
			positions,
			temperatureValues(),
			arguments.option.polynomialDegree
	);
	dumpMatrix(&coefficients);


	SEPARATOR
	printf("\nUkladanie interpolovaneho polynomu do \"temperature_interpolation.txt\"\n\n");

	FILE *outputFile = file("temperature_interpolation.txt", "wt");

	const double
			minPosition = getAt(positions, 0, 0),
			maxPosition = getAt(positions, positions->rows - 1, 0),
			positionDelta = 10.0;
	const size_t length = (maxPosition - minPosition) / positionDelta;

	double position = minPosition;
	for(size_t n = 0; n < length; ++n) {
		const double temperature = kelvinToCelsius(computePolynomial(position, &coefficients));
		outputRow(outputFile, position, &temperature, 1);

		position += positionDelta;
	}

	close(outputFile);


	SEPARATOR
	printf("\nClean up\n\n");

	matrixDelete(&coefficients);

	cleanupTemperature();
	cleanupRootPath();


	return 0;
}
