#include "computor.hpp"



void	parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom) {
	checkComposition(equation);
	normalizeX(equation);

	std::string	s_left_polynom, s_right_polynom;
	splitEquation(equation, s_left_polynom, s_right_polynom);

	spacePolynom(s_left_polynom);
	spacePolynom(s_right_polynom);

	reduceOperators(s_left_polynom);
	reduceOperators(s_right_polynom);

	std::vector<std::string> v_left_polynom, v_right_polynom;
}


void checkComposition(std::string &equation) {
    std::string::size_type pos = equation.find_first_not_of("1234567890xX.*^+-= \t");

    if (pos != std::string::npos)
        errorExit("input error: invalid character '" + std::string(1, equation[pos]) + "'");
}


void	normalizeX(std::string &equation) {
	std::replace(equation.begin(), equation.end(), 'x', 'X');
}


void	checkSyntax(std::string &equation) {
	
}


void	splitEquation(std::string &equation, std::string &left_polynom, std::string &right_polynom) {
    size_t equalSignCount = std::count(equation.begin(), equation.end(), '=');

    if (equalSignCount != 1)
        errorExit("input error: equation must contain exactly one '=' sign.");

    size_t equalPos = equation.find('=');

    left_polynom = equation.substr(0, equalPos);
    right_polynom = equation.substr(equalPos + 1);
}


void	spacePolynom(std::string &polynom) {

}
