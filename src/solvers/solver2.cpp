#include "computor.hpp"



void	solver2(std::map<size_t, double> &polynom) {
	double	delta;
	int		nb_solutions = 0;

	delta = myPow(polynom[1], 2) - 4 * polynom[2] * polynom[0];

	if (!delta)
		nb_solutions = 1;
	else
		nb_solutions = 2;
	
	std::cout << "\tdelta: " << std::fixed << std::setprecision(4) << delta << 	"\n\tsolutions: " << nb_solutions << std::endl;

	if (nb_solutions == 2 && delta > 0)
		std::cout << PINK << "\tresult:" << GOLD << "\n\t\tX1=" << std::fixed << std::setprecision(4) << ((-polynom[1] + mynRoot(delta, 2)) / (2 * polynom[2])) << "\n\t\tX2=" << ((-polynom[1] - mynRoot(delta, 2)) / (2 * polynom[2])) << std::endl;
	else if (nb_solutions == 1)
		std::cout << PINK << "\tresult:" << GOLD << "\n\t\tX=" << std::fixed << std::setprecision(4) << ((-polynom[1] + mynRoot(delta, 2)) / (2 * polynom[2])) << std::endl;
	else {
		Complex	deltaComplex(0, mynRoot(-delta, 2));
		Complex	num1(-polynom[1], 0);
		Complex	num2(-polynom[1], 0);

		num1 = num1 + deltaComplex;
		num2 = num2 - deltaComplex;
		Complex denom(2 * polynom[2], 0);
		std::cout << PINK << "\tresult:" << GOLD << "\n\t\tX1=" << std::fixed << num1 / denom << "\n\t\tX2=" << num2 / denom << std::endl;
	}
}
