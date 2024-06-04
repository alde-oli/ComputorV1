#include "computor.hpp"



void	solver0(std::map<size_t, double> &polynom) {
	std::cout << PINK << "\tresult:" << GOLD << "\n\t\tequality is " << (!polynom[0] ? "true" : "false") << std::endl;
}	