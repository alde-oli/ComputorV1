#include "computor.hpp"



void spacePolynom(std::string &equation) {
	std::string	spacedEquation;
	size_t		len = equation.size();

	for (size_t i = 0; i < len; ++i) {
		char c = equation[i];

		if (c != ' ' && c != '\t' && c != '*')
			spacedEquation += c;

		if (c == ' ' || c == '\t' || i + 1 == len)
			continue ;
		if (isdigit(c)) {
			if (isdigit(equation[i + 1]) || equation[i + 1] == '^' || equation[i + 1] == '.')
				continue ;
			while (i + 1 < len && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == len || equation[i + 1] == '^')
				continue ;
			spacedEquation += ' ';
			
		} else if (c == 'X') {
			if (equation[i + 1] == '^')
				continue ;
			while (i + 1 < len && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == len || equation[i + 1] == '^')
				continue ;
			spacedEquation += ' ';

		} else if (c == '+' || c == '-') {
			while (i + 1 < len && (equation[i + 1] == ' ' || equation[i + 1] == '\t'))
				i++;
			if (i + 1 == len || equation[i + 1] == '+' || equation[i + 1] == '-')
				continue ;
			spacedEquation += ' ';

		} else if (c == '*' && nextNonspaceValue(equation, i) == '*') {
			i = nextNonspacePos(equation, i);
			spacedEquation.pop_back();
			spacedEquation += '^';

		} else if (i + 1 < len && c != '*' && c != '^' && !(c == '.' && std::isdigit(equation[i + 1])))
			spacedEquation += ' ';
	}
	equation = spacedEquation;
}