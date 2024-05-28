#include "computor.hpp"


void spacePolynom(std::string &equation) {
	std::string spacedEquation;

	for (size_t i = 0; i < equation.size(); ++i) {
		char c = equation[i];

		if (c != ' ' && c != '\t')
			spacedEquation += c;

		if (c == ' ' || c == '\t' || i + 1 == equation.size())
			continue ;
		if (isdigit(c)) {
			if (isdigit(equation[i + 1]) || equation[i + 1] == '^')
				continue ;
			while (i + 1 < equation.size() && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == equation.size() || equation[i + 1] == '^')
				continue ;
			spacedEquation += ' ';
		} else if (c == 'X') {
			if (equation[i + 1] == '^')
				continue ;
			while (i + 1 < equation.size() && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == equation.size() || equation[i + 1] == '^')
				continue ;
			spacedEquation += ' ';
		} else if (c == '+' || c == '-') {
			if (equation[i + 1] == '+' || equation[i + 1] == '-')
				continue ;
			while (i + 1 < equation.size() && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == equation.size() || equation[i + 1] == '+' || equation[i + 1] == '-')
				continue ;
			spacedEquation += ' ';
		}
	}
	equation = spacedEquation;
}