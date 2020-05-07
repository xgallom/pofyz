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
#include "../solvers/linear/linearLeastSquares.h"
#include "../equations/polynomial.h"

#define FILE_PATH "/data/temperature.txt"

#define ENTRY_x 0
#define ENTRY_T 1
#define ENTRY_COUNT 2

struct {
	struct Matrix coefficients;
} static data;

struct FileResults {
	struct Matrix x, T;
};

static struct FileResults loadTemperatureFile(const struct Arguments *arguments)
{
	// Open file
	struct Vector fileName;

	if(isNull(&arguments->stringOption.temperature))
		fileName = pathFor(FILE_PATH);
	else
		fileName = copy(&arguments->stringOption.temperature);

	FILE *inputFile = file(asCString(&fileName), "rt");

	delete(&fileName);

	size_t lines = lineCount(inputFile);

	// Load data
	struct FileResults result = {
			.x = matrixColumnVectorDouble(lines),
			.T = matrixColumnVectorDouble(lines)
	};

	double
			*x = asMDouble(&result.x),
			*T = asMDouble(&result.T),
			parsedBuffer[ENTRY_COUNT];
	char buffer[BUFSIZ];

	while(lines--) {
		// Read line
		fail(
				fgets(buffer, BUFSIZ, inputFile) == NULL,
				"Failed reading line from file \"" FILE_PATH "\"\n"
		);

		// Parse doubles
		switch(parseDoubles(buffer, parsedBuffer, ENTRY_COUNT)) {
			case ENTRY_COUNT:
				// Exactly 2 doubles
				*x++ = parsedBuffer[ENTRY_x];
				*T++ = celsiusToKelvin(parsedBuffer[ENTRY_T]);
				break;

			case 0:
				// Empty row
				break;

			default:
				// Not exactly 2 doubles
				close(inputFile);
				die("Failed parsing " TO_STR(ENTRY_COUNT) " doubles from \"" FILE_PATH "\"\n");
		}
	}

	// Resize result
	matrixResize(&result.x, x - asMDouble(&result.x), KEEP_SIZE);
	matrixResize(&result.T, T - asMDouble(&result.T), KEEP_SIZE);

	close(inputFile);

	return result;
}

void initializeTemperature(const struct Arguments *arguments)
{
	struct FileResults results = loadTemperatureFile(arguments);

	data.coefficients = solveLinearLeastSquares(
			&results.x,
			&results.T,
			arguments->intOption.polynomialDegree
	);

	matrixDelete(&results.x);
	matrixDelete(&results.T);
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
		printf("%g x^{%zu} %s",
			   asCMDouble(&data.coefficients)[n],
			   n,
			   n == data.coefficients.length - 1 ? "" : "+ "
		);
	printf("\n");
}
