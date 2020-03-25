//
// Created by xgallom on 3/25/20.
//

#include "temperature.h"
#include "../core/file.h"
#include "../core/vector.h"
#include "../core/error.h"
#include "../core/parse.h"
#include "../core/rootPath.h"
#include "../core/toStr.h"
#include "../arguments/arguments.h"
#include "../equations/general.h"

#define FILE_PATH "/data/temperature.txt"

#define ENTRY_x 0
#define ENTRY_T 1
#define ENTRY_COUNT 2

struct {
	struct Vector x, T, fileName;
} static data;

void initializeTemperature(const struct Arguments *arguments)
{
	if(isNull(&arguments->dataFile.temperature))
		data.fileName = pathFor(FILE_PATH);
	else
		data.fileName = copy(&arguments->dataFile.temperature);

	FILE *inputFile = file(asCString(&data.fileName), "rt");

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
	delete(&data.fileName);
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

	printf("Data from file \"%s\" in format [x, T]:\n", asCString(&data.fileName));
	for(int i = 0; i < data.x.length; ++i)
		printf("   [%8.2f m, %5.2f K]\n", *x++, *T++);
	printf("\n");
}
