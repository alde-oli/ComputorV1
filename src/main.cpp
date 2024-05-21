#include "computor.hpp"

int	main(int ac, char **av) {
	if (ac != 2)
		errorExit("input error: wrong number of arguments\nusage: a * X^(n) + b * X^(n - 1) + ... + n * X^0 = A * X^(N) + B * X^(N - 1) + ... + N * X^0");

	std::string input(av[1]);

	if (input == "HELP") {
		std::cout << std::endl << "usage: a * X^(n) + b * X^(n - 1) + ... + n * X^0 = A * X^(N) + B * X^(N - 1) + ... + N * X^0" << std::endl << std::endl;
		std::cout << "n and N must be positive integers" << std::endl << std::endl;
		std::cout << "this program only solves equations of degree up to 3, equations of higher degree can only be reduced" << std::endl << std::endl;
		exit(0);
	}
	std::cout << std::endl;
	computor(std::string(av[1]));
	std::cout << std::endl;
}