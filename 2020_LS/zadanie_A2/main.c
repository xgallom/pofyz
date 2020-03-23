#include "core/vector.h"
#include "core/output.h"
#include "constants.h"
#include "arguments.h"
#include "solvers/euler.h"
#include "solvers/rungeKutta.h"
#include "equations/analytical.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	const struct Arguments arguments = parseArguments(argc, argv);
	dumpParameters(&arguments);
	initializeConstants(&arguments);

	struct Vector
			x = vectorDouble(steps),
			v = vectorDouble(steps);

	size_t length = solveEuler(&x, &v);
	printf("Euler solution steps: %zu\n", length);
	outputDoubles("euler.txt", asCDouble(&x), asCDouble(&v), length);

	length = solveRungeKutta(&x, &v);
	printf("Runge Kutta solution steps: %zu\n", length);
	outputDoubles("rungeKutta.txt", asCDouble(&x), asCDouble(&v), length);

	length = analytical(&x, &v);
	printf("Analytical solution steps: %zu\n", length);
	outputDoubles("analytical.txt", asCDouble(&x), asCDouble(&v), length);

	printf(
			"\nM: %f kg/mol\n"
			"Analytical tD: %f s\n"
			"Analytical vD: %f m/s\n",
			M,
			tD(),
			vD()
	);

	delete(&x);
	delete(&v);

	return 0;
}
