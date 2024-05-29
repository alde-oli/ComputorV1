#include "computor.hpp"


void	reduceEquation(std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom) {
	size_t			equation_degree;

	equation_degree = left_polynom.rbegin()->first;
	equation_degree = equation_degree >= right_polynom.rbegin()->first ? equation_degree : right_polynom.rbegin()->first;

	while (equation_degree > 0)
		if (right_polynom.find(equation_degree--) != right_polynom.end())
			left_polynom[equation_degree + 1] -= right_polynom[equation_degree + 1];
	
	if (right_polynom.find(0) != right_polynom.end())
			left_polynom[0] -= right_polynom[0];
	
	std::cout << MAGENTA << "Reduced equation:" << CYAN << std::endl;

	bool			first = true;
	unsigned int	deg = left_polynom.rbegin()->first;
		while(deg && !left_polynom[deg])
			deg--;
	for (size_t i = 0; i <= deg; i++) {
		std::cout << (left_polynom[i] >= 0 ? (first ? "" : "+ ") : (first ? "-" : "- ")) << (left_polynom[i] < 0 ? - left_polynom[i] : left_polynom[i]) << " * X^" << i << " ";
		if (first)
			first = false;
	}
	std::cout << "= 0" << RESET << std::endl;
}
