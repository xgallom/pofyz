//
// Created by xgallom on 4/2/20.
//

#include "polynomial.h"
#include "../core/matrix.h"

// Optimized power function for integer exponent
double nthDegreePolynomial(double x, size_t n)
{
	double result = 1.0;

	while(n--)
		result *= x;

	return result;
}

// Avoid power call recomputation by reusing last power
double computePolynomial(double x, const struct Matrix *coefficients)
{
	size_t count = coefficients->length;
	const double *coefficient = asCMDouble(coefficients);

	double power = 1.0, result = 0.0;
	while(count--) {
		result += *coefficient++ * power;
		power *= x;
	}

	return result;
}
