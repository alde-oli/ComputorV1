#include "computor.hpp"


void	splitEquation(std::string &equation, std::string &left_polynom, std::string &right_polynom) {
	size_t	equalSignCount = std::count(equation.begin(), equation.end(), '=');

	if (equalSignCount != 1)
		errorExit("input error: equation must contain exactly one '=' sign.");

	size_t equalPos = equation.find('=');

	left_polynom = equation.substr(0, equalPos);
	right_polynom = equation.substr(equalPos + 1);
}
