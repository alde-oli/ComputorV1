#include "computor.hpp"


void	checkSyntax(const std::string &equation) {
	char			c = 0;
	char			next_value = 0;
	const int		len = equation.length();

	for (int i = 0; i < len; i = nextNonspacePos(equation, i)) {
		if (i >= len)
			return ;
		next_value = nextNonspaceValue(equation, i);
		if (std::isdigit((c = equation[i]))) {

		} else if (std::strchr("+-", c)) {
			if (std::strchr("*^.", next_value))
				pointError(equation, i, "invalid symbol combination");
		} else {
			switch (c) {
				case 'X':

				case '*':

				case '^':

				case '.':
			}
		}
	}
}