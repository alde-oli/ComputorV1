#include "computor.hpp"



void	pointError(const std::string &equation, int i, const std::string &error_msg) {
	std::cerr << std::endl << RED << "error:" << RESET << std::endl;
	std::cerr << "\"" << equation << "\"" << YELLOW << std::endl;
	for (int j = 0; j < i; j++)
		std::cerr << " ";
	std::cerr << " ^" << std::endl;
	for (int j = 0; j < i; j++)
		std::cerr << "_";
	std::cerr << "_|: " << error_msg << RESET << std::endl; 
	exit(1);
}


void	errorExit(const std::string msg) {
	std::cerr << RED << msg << RESET << std::endl;
	exit(1);
}
