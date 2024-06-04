#include "computor.hpp"



void	checkSyntax(const std::string &equation) {
	char			c = 0;
	char			next_value = 0;
	const int		len = equation.length();
	int				first = 0;
	
	if (len == 0 || (first = std::strchr(" \t", equation[first]) ? nextNonspacePos(equation, 0) : 0) == len)
		errorExit("empty polynom");
	if (std::strchr("*^", equation[first]))
		pointError(equation, first, "missing term before operator");

	for (int i = first; i < len; i = nextNonspacePos(equation, i)) {
		if (i == len)
			return ;
		c = equation[i];
		next_value = nextNonspaceValue(equation, i);
		if (std::strchr("+-*^", c) && !next_value)
			pointError(equation, i, "missing term after operator");
		else if (std::strchr("+-", c) && std::strchr("*^", next_value))
			pointError(equation, i, "invalid operators combination");
		else if (c == '*' && std::strchr("^+-", next_value))
			pointError(equation, i, "invalid operators combination");
		else if (c == '^' && !std::isdigit(next_value))
			pointError(equation, i, "invalid operators combination");
	}
	
	for (int i = first; i < len; i = nextNonspacePos(equation, i)) {
		if (equation[i] == '.') {
			if ((!i || !std::isdigit(equation[i - 1])) && (i == len - 1 || !std::isdigit(equation[i + 1])))
				pointError(equation, i, "invalid float");

		} else if (equation[i] == '^') {
			next_value = nextNonspaceValue(equation, i);
			i = nextNonspacePos(equation, i);
			while (nextNonspacePos(equation, i) == i + 1 && i + 1 != len && !std::strchr("*+-X", equation[i + 1]))
				if (equation[++i] == '.')
					pointError(equation, i, "float used as exponant");

		} else if (equation[i] == '*')
			if (nextNonspaceValue(equation, i) == '*' && (nextNonspaceValue(equation, nextNonspacePos(equation, i)) == '*' || nextNonspaceValue(equation, nextNonspacePos(equation, i)) == 'X'))
				pointError(equation, i, "too many consecutives \'*\'");
	}
	if (verbose)
		std::cout << GREEN << "Syntax OK" << RESET << std::endl << std::endl;
}
