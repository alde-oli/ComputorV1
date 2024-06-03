#include "computor.hpp"

static void	resolveTerm(std::string &term, std::map<size_t, double> &polynom);
static void resolvePowGroup(std::string &group);



void resolvePolynom(std::vector<std::string> str_polynom, std::map<size_t, double> &polynom) {
	for (std::vector<std::string>::iterator it = str_polynom.begin(); it != str_polynom.end(); it++)
		resolveTerm(*it, polynom);
}


static void	resolveTerm(std::string &term, std::map<size_t, double> &polynom) {
	std::vector<std::string>	tokens;
	std::stringstream			ss(term);
	std::string					token;
	double						coeff = 1.0;
	size_t						exp = 0;

	while (std::getline(ss, token, ' ')) {
		resolvePowGroup(token);
		tokens.push_back(token);
	}
	if (tokens.empty())
		return ;

	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		if ((*it)[0] == 'X') {
			if ((*it).length() == 1)
				exp += 1;
			else
				exp += strToSizeT((*it).substr(2));
		} else
			coeff *= strToDouble(*it);
	}
	polynom[exp] += coeff;
}


static void resolvePowGroup(std::string &group) {
	std::vector<std::string>	tokens;
	std::stringstream			ss(group);
	std::string					token;

	if (group.find_first_of("^") == std::string::npos)
		return ;

	while (std::getline(ss, token, '^'))
		tokens.push_back(token);
	if (tokens.empty())
		return ;

	bool isVariable = (tokens[0].find_first_of("X") != std::string::npos);

	if (isVariable) {
		size_t result = strToSizeT(tokens.back());
		for (int i = tokens.size() - 2; i > 0; --i) {
			size_t exp = strToSizeT(tokens[i]);
			result = static_cast<size_t>(myPow(exp, result));
			if (result > std::numeric_limits<size_t>::max()) {
				result = std::numeric_limits<size_t>::max();
				break;
			}
		}
		std::ostringstream oss;
		oss << tokens[0] << "^" << result;
		group = oss.str();
	} else {
		double result = strToDouble(tokens.back());
		for (int i = tokens.size() - 2; i >= 0; --i) {
			double base = strToDouble(tokens[i]);
			result = myPow(base, result);
			if (result == std::numeric_limits<double>::infinity() || result == -std::numeric_limits<double>::infinity()) {
				break;
			}
		}
		group = doubleToStr(result);
	}
}