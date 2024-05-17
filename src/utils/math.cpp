#include "computor.hpp"


double	myPow(double x, int exp) {
	double	result = 1.0;
	bool	is_negative = exp < 0;

	if (exp < 0)
		exp = -exp;

	while (exp > 0) {
		if (exp % 2 == 1)
			result *= x;
		x *= x;
		exp /= 2;
	}
	if (is_negative)
		result = 1.0 / result;
	return result;
}


double	mynRoot(double x, int n) {
	if (x < 0 && n % 2 == 0)
		errorExit("mySqrt error: cannot resolve an even root of negative number");
	if (n <= 0)
		errorExit("mySqrt error: root degree must be positive");

	double a = x;
	while (true) {
		double a_new = (1.0 / n) * ((n - 1) * a + x / myPow(a, n - 1));
		double fabs_delta = a_new - a >= 0 ? a_new - a : -(a_new - a);
		if (fabs_delta < NROOT_TOLERANCE)
			return a_new;
		a = a_new;
	}
}


int	myFactorial(unsigned int x) {
	int	result = x;

	if (x == 0)
		return 1;
	while (x-- > 1)
		result *= x;
	return result;
}


double	myCos(double x) {
	double	cos = 0;

	for (int n = 0; n < TRIGO_RECURSION; n++)
		cos += myPow(-1, n) * myPow(x, 2 * n) / myFactorial(2*n);
	return cos;
}


double	mySin(double x)  {
	double	sin = 0;

	for (int n = 0; n < TRIGO_RECURSION; n++)
		sin += myPow(-1, n) * myPow(x, (2*n + 1)) / myFactorial(2*n + 1);
	return sin;
}