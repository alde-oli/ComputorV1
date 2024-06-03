#include "computor.hpp"



void	parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom) {
	checkComposition(equation);
	normalizeX(equation);

	std::string	s_left_polynom, s_right_polynom;
	splitEquation(equation, s_left_polynom, s_right_polynom);

	checkSyntax(s_left_polynom);
	checkSyntax(s_right_polynom);

	spacePolynom(s_left_polynom);
	spacePolynom(s_right_polynom);

	reduceOperators(s_left_polynom);
	reduceOperators(s_right_polynom);

	std::vector<std::string> v_left_polynom, v_right_polynom;
	splitPolynom(s_left_polynom, v_left_polynom);
	splitPolynom(s_right_polynom, v_right_polynom);

	resolvePolynom(v_left_polynom, left_polynom);
	resolvePolynom(v_right_polynom, right_polynom);
}
