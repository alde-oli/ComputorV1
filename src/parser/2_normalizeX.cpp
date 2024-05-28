#include "computor.hpp"


void	normalizeX(std::string &equation) {
	std::replace(equation.begin(), equation.end(), 'x', 'X');
}
