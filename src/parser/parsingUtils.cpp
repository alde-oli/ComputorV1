#include "computor.hpp"


double	stringToDouble(const std::string& str) {
	std::istringstream	iss(str);
	double				result;

	iss >> result;
	if (iss.fail() || !iss.eof())
		errorExit("Conversion to double failed for: " + str);
	return result;
}


int	stringToInt(const std::string& str) {
	std::istringstream	iss(str);
	int					result;

	iss >> result;
	if (iss.fail() || !iss.eof())
		errorExit("Conversion to int failed for: " + str);
	return result;
}


char	nextNonspaceValue(const std::string &equation, int i) {
	const int	len = equation.length();
	char		c = 0;

	while (++i < len)
		if ((c = equation[i]) != ' ' && c != '\t')
			return c;
	return 0;
}


int	nextNonspacePos(const std::string &equation, int i) {
	const int	len = equation.length();
	char		c = 0;

	while (++i < len)
		if ((c = equation[i]) != ' ' && c != '\t')
			return i;
	return len;
}
