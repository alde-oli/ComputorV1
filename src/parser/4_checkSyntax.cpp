#include "computor.hpp"


void	checkSyntax(const std::string &equation) {
	char			c = 0;
	char			next_value = 0;
	const int		len = equation.length();
	bool			in_exp = false;
	bool			is_float = false;

	for (int i = 0; i < len; i = nextNonspacePos(equation, i)) {
		if (i == len)
			return ;
		c = equation[i];
		next_value = nextNonspaceValue(equation, i);
		if (std::strchr("+-*^", c) && !next_value)
			pointError(equation, i, "missing term after symbol");
		if (std::strchr("+-", c) && std::strchr("*^", next_value)) {
			pointError(equation, i, "invalid symbols combination");
		} else if (c == '*' && std::strchr("^+-", next_value))
			pointError(equation, i, "invalid symbols combination");
		else if (c == '^' && std::strchr("*^.+-X", next_value))
			pointError(equation, i, "invalid symbols combination");
	}

	for (int i = 0; i < len; i = nextNonspacePos(equation, i)) {
		if (i == len)
			return ;
		c = equation[i];
		next_value = nextNonspaceValue(equation, i);
		
	}
}
