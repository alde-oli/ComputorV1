#include "computor.hpp"



void	solver2(std::map<size_t, double> &polynom) {
	double	delta;
	int		nb_solutions = 0;

	delta = myPow(polynom[1], 2) - 4 * polynom[2] * polynom[0];

	if (delta > 0)
		nb_solutions = 2;
	else if (delta == 0)
		nb_solutions = 1;
	
	std::cout << "delta: " << std::fixed << std::setprecision(4) << delta << 	"\nsolutions: " << nb_solutions << std::endl;

	if (nb_solutions == 2)
		std::cout << PINK << "result:" << GOLD << "\n\tX1=" << std::fixed << std::setprecision(4) << ((-polynom[1] + mynRoot(delta, 2)) / (2 * polynom[2])) << "\n\tX2=" << ((-polynom[1] - mynRoot(delta, 2)) / (2 * polynom[2])) << std::endl;
	else if (nb_solutions == 1)
		std::cout << PINK << "result:" << GOLD << "\n\tX=" << std::fixed << std::setprecision(4) << ((-polynom[1] + mynRoot(delta, 2)) / (2 * polynom[2])) << std::endl;
	else
		std::cout << PINK << "result:" << GOLD << "\n\tno real solution" << std::endl;
}
