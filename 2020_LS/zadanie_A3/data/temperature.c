//
// Created by xgallom on 3/25/20.
//

#include "temperature.h"
#include "../core/file.h"
#include "../core/vector.h"
#include "../core/error.h"
#include "../core/parse.h"
#include "../core/toStr.h"
#include "../equations/general.h"

#define FILE_PATH "data/temperature.txt"

#define ENTRY_x 0
#define ENTRY_T 1
#define ENTRY_COUNT 2

struct {
	struct Vector x, T;
} static data;

void initializeTemperature(void)
{
	FILE *inputFile = file(FILE_PATH, "rt");
	size_t lines = lineCount(inputFile);

	data.x = vectorDouble(lines);
	data.T = vectorDouble(lines);

	double
			*x = asDouble(&data.x),
			*T = asDouble(&data.T),
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

	resize(&data.x, x - asDouble(&data.x));
	resize(&data.T, T - asDouble(&data.T));

	close(inputFile);
}

void cleanupTemperature(void)
{
	delete(&data.x);
	delete(&data.T);
}

double temperatureFor(double x)
{
	// TODO: Interpolate
	return 0.0;
}

void dumpTemperature(void)
{
	const double
			*x = asCDouble(&data.x),
			*T = asCDouble(&data.T);

	printf("Data from file \"" FILE_PATH "\" in format [x, T]:\n");
	for(int i = 0; i < data.x.length; ++i)
		printf("   [%8.2f m, %5.2f K]\n", *x++, *T++);
	printf("\n");
}
