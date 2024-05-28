#include "computor.hpp"


void	pointError(const std::string &equation, int i, const std::string &error_msg) {
	std::cout << "\terror:" << std::endl;
	std::cout << equation << std::endl;
	for (int j = 0; j < i; j++)
		std::cout << "_";
	std::cout << "^" << error_msg << std::endl; 
}


void	errorExit(const std::string msg) {
	std::cerr << msg << std::endl;
	exit(1);
}
