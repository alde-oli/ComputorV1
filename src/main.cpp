#include "computor.hpp"

int	main(int ac, char **av) {
	if (ac != 2)
		errorExit("input error: no input");
	computor(std::string(av[1]));
}