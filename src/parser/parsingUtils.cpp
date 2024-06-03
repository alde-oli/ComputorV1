#include "computor.hpp"



double	strToDouble(const std::string& str) {
	std::istringstream	iss(str);
	double				result;

	iss >> result;
	if (iss.fail() || !iss.eof())
		errorExit("Conversion to double failed for: " + str);
	return result;
}


size_t	strToSizeT(const std::string& str) {
	std::istringstream	iss(str);
	size_t				result;

	iss >> result;
	if (iss.fail() || !iss.eof())
		errorExit("Conversion to size_t failed for: " + str);
	return result;
}


std::string	doubleToStr(double n) {
	std::ostringstream	oss;
	oss << n;
	return oss.str();
}


std::string	sizeTToStr(size_t n) {
	std::ostringstream	oss;
	oss << n;
	return oss.str();
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
