#include <stdio.h>

#include "solvers/euler.h"
#include "solvers/rungeKutta.h"
#include "utility.h"
#include "constants.h"
#include "analytical.h"

int main()
{
	double
			*x = vectorDouble(steps),
			*v = vectorDouble(steps);

	solveEuler(x, v);
	outputDoubles("euler.txt", x, v, steps);

	solveRungeKutta(x, v);
	outputDoubles("rungeKutta.txt", x, v, steps);

	analytical(x, v);
	outputDoubles("analytical.txt", x, v, steps);

	printf(
			"M: %f kg/mol\n"
			"tD: %f s\n"
			"vD: %f m/s\n",
			M,
			tD(),
			vD()
	);

	return 0;
}
