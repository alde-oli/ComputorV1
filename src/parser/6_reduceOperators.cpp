#include "computor.hpp"


void reduceOperators(std::string &equation) {
	std::string reducedEquation;
	char lastOperator = '\0';

	for (size_t i = 0; i < equation.size(); ++i) {
		char c = equation[i];

		if (c == '+' || c == '-') {
			if (lastOperator == '\0')
				lastOperator = c;
			else {
				if (lastOperator == '+' && c == '+')
					lastOperator = '+';
				else if (lastOperator == '-' && c == '-')
					lastOperator = '+';
				else if ((lastOperator == '+' && c == '-') || (lastOperator == '-' && c == '+'))
					lastOperator = '-';
			}
		} else {
			if (lastOperator != '\0') {
				reducedEquation += lastOperator;
				lastOperator = '\0';
			}
			reducedEquation += c;
		}
	}
	if (lastOperator != '\0')
		reducedEquation += lastOperator;

	equation = reducedEquation;
}