#include "computor.hpp"



int	main(int ac, char **av) {
	std::string	input;

	if (ac == 3 && !std::strcmp("-v", av[1])) {
		verbose = true;
		input = std::string(av[2]);
	} else if (ac != 2)
		errorExit("input error: wrong number of arguments\nusage: a * X^(n) + b * X^(n - 1) + ... + n * X^0 = A * X^(N) + B * X^(N - 1) + ... + N * X^0");
	else
		input = std::string(av[1]);

	if (input == "HELP") {
		std::cout << BLUE << std::endl << "usage:" << GREEN <<" a * X^(n)" << CYAN <<" +" << GREEN <<" b * X^(n - 1) " <<CYAN <<"+" << GREEN << " ... " << CYAN <<"+" << GREEN << " n * X^0 " << YELLOW << "=" << GREEN <<" A * X^(N) " << CYAN <<"+" << GREEN <<" B * X^(N - 1)" << CYAN <<"+" << GREEN <<" ... " << CYAN << "+" << GREEN <<" N * X^0" << std::endl << std::endl;
		std::cout << BLUE << "n and N must be positive integers" << std::endl;
		std::cout << BLUE << "authorised characters are: 0 1 2 3 4 5 6 7 8 9 . x X + - * ^ \\t \' \'" << std::endl << std::endl;
		std::cout << "this program only solves equations of degree up to 3, equations of higher degree can only be reduced" << RESET << std::endl << std::endl;
		exit(0);
	}
	computor(input);
	std::cout << RESET << std::endl;
}
