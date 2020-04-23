//
// Created by xgallom on 3/25/20.
//

#include "temperature.h"
#include "../core/file.h"
#include "../core/matrix.h"
#include "../core/error.h"
#include "../core/parse.h"
#include "../core/rootPath.h"
#include "../core/toStr.h"
#include "../arguments/arguments.h"
#include "../equations/general.h"
#include "../solvers/linearLeastSquares.h"
#include "../equations/polynomial.h"

#define FILE_PATH "/data/temperature.txt"

#define ENTRY_x 0
#define ENTRY_T 1
#define ENTRY_COUNT 2

struct {
	struct Matrix coefficients;
} static data;

void initializeTemperature(const struct Arguments *arguments)
{
	struct Vector fileName;

	if(isNull(&arguments->dataFile.temperature))
		fileName = pathFor(FILE_PATH);
	else
		fileName = copy(&arguments->dataFile.temperature);

	FILE *inputFile = file(asCString(&fileName), "rt");

	size_t lines = lineCount(inputFile);

	struct Matrix
			vectorX = matrixColumnVectorDouble(lines),
			vectorT = matrixColumnVectorDouble(lines);

	double
			*x = asMDouble(&vectorX),
			*T = asMDouble(&vectorT),
			parsedBuffer[ENTRY_COUNT];
	char buffer[BUFSIZ];

	while(lines--) {
		fail(
				fgets(buffer, BUFSIZ, inputFile) == NULL,
				"Failed reading line from file \"" FILE_PATH "\"\n"
		);

		switch(parseDoubles(buffer, parsedBuffer, ENTRY_COUNT)) {
			case ENTRY_COUNT:
				*x++ = parsedBuffer[ENTRY_x];
				*T++ = celsiusToKelvin(parsedBuffer[ENTRY_T]);
				break;

			case 0:
				break;

			default:
				close(inputFile);
				die("Failed parsing " TO_STR(ENTRY_COUNT) " doubles from \"" FILE_PATH "\"\n");
		}
	}

	matrixResize(&vectorX, x - asMDouble(&vectorX), KEEP_SIZE);
	matrixResize(&vectorT, T - asMDouble(&vectorT), KEEP_SIZE);

	data.coefficients = solveLinearLeastSquares(
			&vectorX,
			&vectorT,
			arguments->option.polynomialDegree
	);

	matrixDelete(&vectorX);
	matrixDelete(&vectorT);

	close(inputFile);
}

void cleanupTemperature(void)
{
	matrixDelete(&data.coefficients);
}

double temperatureFor(double x)
{
	return computePolynomialUnsafe(x, asCMDouble(&data.coefficients), data.coefficients.length);
}

void dumpTemperature(void)
{
	printf("Temperature interpolation coefficients:\n");
	for(size_t n = 0; n < data.coefficients.length; ++n)
		printf("%d: %g\n", n, asCMDouble(&data.coefficients)[n]);
	printf("\n");
}
