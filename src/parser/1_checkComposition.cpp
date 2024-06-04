#include "computor.hpp"



void checkComposition(const std::string &equation) {
	std::string::size_type pos = equation.find_first_not_of("1234567890xX.*^+-= \t");

	if (pos != std::string::npos)
		pointError(equation, pos, "invalid character");
	if (verbose)
		std::cout << GREEN << "Composition OK" << RESET << std::endl << std::endl;
}
