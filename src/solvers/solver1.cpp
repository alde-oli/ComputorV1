#include "computor.hpp"



void	solver1(std::map<size_t, double> &polynom) {
	std::cout << PINK << "\tresult:" << GOLD << "\n\t\tX=" << (-polynom[0] / polynom[1]) << std::endl;
}