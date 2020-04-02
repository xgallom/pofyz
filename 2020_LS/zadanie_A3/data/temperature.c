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

#define FILE_PATH "/data/temperature.txt"

#define ENTRY_x 0
#define ENTRY_T 1
#define ENTRY_COUNT 2

struct {
	struct Matrix x, T;
	struct Vector fileName;
} static data;

void initializeTemperature(const struct Arguments *arguments)
{
	if(isNull(&arguments->dataFile.temperature))
		data.fileName = pathFor(FILE_PATH);
	else
		data.fileName = copy(&arguments->dataFile.temperature);

	FILE *inputFile = file(asCString(&data.fileName), "rt");

	size_t lines = lineCount(inputFile);

	data.x = matrixColumnVectorDouble(lines);
	data.T = matrixColumnVectorDouble(lines);

	double
			*x = asMDouble(&data.x),
			*T = asMDouble(&data.T),
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

	matrixResize(&data.x, x - asMDouble(&data.x), KEEP_SIZE);
	matrixResize(&data.T, T - asMDouble(&data.T), KEEP_SIZE);

	close(inputFile);
}

void cleanupTemperature(void)
{
	matrixDelete(&data.x);
	matrixDelete(&data.T);
	delete(&data.fileName);
}

const struct Matrix *temperaturePositions() { return &data.x; }
const struct Matrix *temperatureValues() { return &data.T; }
size_t temperatureCount() { return data.x.length; }

void dumpTemperature(void)
{
	const double
			*x = asCMDouble(&data.x),
			*T = asCMDouble(&data.T);
	const size_t count = temperatureCount();

	printf("Data from file \"%s\" in format [x, T]:\n", asCString(&data.fileName));
	for(int i = 0; i < count; ++i)
		printf("   [%10.2f m, %10.2f K]\n", *x++, *T++);
	printf("\n");
}
