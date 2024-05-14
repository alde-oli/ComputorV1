#include "computor.hpp"


int	computor(std::string input) {
		std::map<size_t, double>	leftPolynom;
		std::map<size_t, double>	rightPolynom;

		unsigned int				deg = 0;

		void						(*solvers[5])(std::map<size_t, double>) = {solver0, solver1, solver2, solver3, solver4};


		parseEquation(input, leftPolynom, rightPolynom);

		reduceEquation(leftPolynom, rightPolynom);

		deg = leftPolynom.rbegin()->first;

		std::cout << "Polynomial degree: " << deg << std::endl;

		solvers[deg](leftPolynom);
}
