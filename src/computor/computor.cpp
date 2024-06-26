#include "computor.hpp"



void	computor(std::string input) {
		std::map<size_t, double>	left_polynom;
		std::map<size_t, double>	right_polynom;
		unsigned int				deg = 0;
		void						(*solvers[4])(std::map<size_t, double> &) = {solver0, solver1, solver2, solver3};

		parseEquation(input, left_polynom, right_polynom);
		
		std::cout << RESET << std::endl;
		std::cout << std::endl << VIOLET << "simplified equation: \n\t" << CYAN ;
		bool	first = true;
		deg = left_polynom.rbegin()->first;
		while(deg && !left_polynom[deg])
			deg--;
		for (size_t i = 0; i <= deg; i++) {
			if (left_polynom[i])
				std::cout << (left_polynom[i] >= 0 ? (first ? "" : "+ ") : (first ? "-" : "- ")) << (left_polynom[i] < 0 ? - left_polynom[i] : left_polynom[i]) << " * X^" << i << " ";
			if (first)
				first = false;
		}
		std::cout << "= ";
		first = true;
		deg = right_polynom.rbegin()->first;
		while(deg && !right_polynom[deg])
			deg--;
		for (size_t i = 0; i <= deg; i++) {
			if (right_polynom[i])
				std::cout << (right_polynom[i] >= 0 ? (first ? "" : "+ ") : (first ? "-" : "- ")) << (right_polynom[i] < 0 ? - right_polynom[i] : right_polynom[i]) << " * X^" << i << " ";
			if (first)
				first = false;
		}
		std::cout << RESET << std::endl;

		reduceEquation(left_polynom, right_polynom);

		deg = left_polynom.rbegin()->first;
		while(deg && !left_polynom[deg])
			deg--;
		std::cout << VIOLET << "polynomial degree: \n\t" << CYAN << deg << RESET << std::endl;

		if (deg <= 3) {
			std::cout << std::endl << VIOLET << "Solving equation:" << RESET << std::endl;
			solvers[deg](left_polynom);
		} else
			std::cout << YELLOW << "cannot resolve equations over 3rd degree" << RESET << std::endl;
}

