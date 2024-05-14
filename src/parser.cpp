#include "computor.hpp"

static void						removeGarbage(std::string &str);
static std::vector<std::string>	splitPolynomial(const std::string& poly);
static void						resolveTerm(std::string& term, std::map<size_t, double>& polynom);
static void						validateTerm(std::string& term, bool &isNegative);
static double					computePower(const std::string& powerGroup);
static std::vector<std::string>	splitTerm(const std::string& term);
static std::vector<std::string>	splitPolynomial(const std::string& poly);
static void						msg_exit(std::string msg);
static double					myPow(double base, int exp);



void parseEquation(std::string &equation, std::map<size_t, double> &leftPolynom, std::map<size_t, double> &rightPolynom) {
	removeGarbage(equation);

	size_t						invalid_pos;
	if ((invalid_pos = equation.find_first_not_of("0123456789xX*^+-=")) != std::string::npos)
		msg_exit("input error: invalid token: \'" + std::string(1, equation[invalid_pos]) + "\'");

	size_t						pos = equation.find('=');
	if (pos == std::string::npos)
		msg_exit("input error: missing token: \'=\'");

	std::string					leftStr = equation.substr(0, pos);
	std::string					rightStr = equation.substr(pos + 1);

	std::vector<std::string>	leftTermsStr = splitPolynomial(leftStr);
	std::vector<std::string>	rightTermsStr = splitPolynomial(rightStr);

	for (size_t i = 0; i < leftTermsStr.size(); i++)
		resolveTerm(leftTermsStr[i], leftPolynom);

	for (size_t i = 0; i < rightTermsStr.size(); i++)
		resolveTerm(rightTermsStr[i], rightPolynom);
}


static void	removeGarbage(std::string &str) {
	size_t	pos;
	while ((pos = str.find_first_of(" \t\n\r\x0B")) != std::string::npos)
			str.erase(pos, 1);
}


static std::vector<std::string> splitPolynomial(const std::string& poly) {
	std::vector<std::string>	terms;
	std::string					term;
	int							start = 0;

	for (int i = 0; i < poly.length(); i++) {
		if ((poly[i] == '+' || poly[i] == '-') && i > 0) {
			term = poly.substr(start, i - start);
			if (term[0] == '+')
				term = term.substr(1);
			terms.push_back(term);
			start = i;
		}
	}
	term = poly.substr(start);
	if (term[0] == '+')
		term = term.substr(1);
	terms.push_back(term);
	return terms;
}


static void resolveTerm(std::string& term, std::map<size_t, double>& polynom) {
	bool						isNegative = false;
	
	validateTerm(term, isNegative);

	std::vector<std::string>	parts = splitTerm(term);
	double						coefficient = 1.0;
	size_t						exponent = 0;

	for (const std::string& part : parts) {
		if (part.find('X') != std::string::npos) {
			size_t expPos = part.find('^');
			if (expPos != std::string::npos) {
				std::string expPart = part.substr(expPos + 1);
				exponent += static_cast<size_t>(computePower(expPart));
			} else
				exponent += 1;
		} else
			coefficient *= computePower(part);
	}
	if (isNegative)
		coefficient = -coefficient;

	polynom[exponent] += coefficient;
}


static void validateTerm(std::string& term, bool &isNegative) {;
	size_t		x_pos;

	if (!term.length())
		msg_exit("input error: consecutive \'+\' operators");

	while ((x_pos = term.find('x')) != std::string::npos)
		term[x_pos] = 'X';
	if (term[0] == '-') {
		isNegative = true;
		term = term.substr(1);
	}

	if (term[0] == '*' || term[0] == '^' || term[term.length() - 1] == '*' || term[term.length() - 1] == '^')
		msg_exit("input error: unexpected operator in term " + term);
	
	for (size_t i = 0; i < term.length() - 1; ++i)
	{
		if (term[i] == '^' && term[i + 1] == 'X')
			msg_exit("input error: variable used as exponent in term " + term);
		if ((term[i] == '*' || term[i] == '^') && (term[i + 1] == '*' || term[i + 1] == '^'))
			msg_exit("input error: consecutive operators in term " + term);
	}

}


static double computePower(const std::string& powerGroup) {
	std::vector<double>	numbers;
	std::string			number;

	for (size_t i = 0; i < powerGroup.size(); ++i) {
		if (isdigit(powerGroup[i]) || powerGroup[i] == '.')
			number += powerGroup[i];
		else if (powerGroup[i] == '^') {
			if (!number.empty()) {
				numbers.push_back(stod(number));
				number.clear();
			}
		}
	}
	if (!number.empty())
		numbers.push_back(stod(number));

	double				result = numbers.back();
	for (int i = numbers.size() - 2; i >= 0; --i)
		result = myPow(numbers[i], result);

	return result;
}


static std::vector<std::string> splitTerm(const std::string& term) {
	std::vector<std::string>	parts;
	std::string					currentPart;
	bool						inExponent = false;

	for (size_t i = 0; i < term.length(); ++i) {
		char c = term[i];

		if (isdigit(c)) {
			if (!inExponent && !currentPart.empty() && !isdigit(currentPart.back()) && currentPart.back() != '^') {
				parts.push_back(currentPart);
				currentPart.clear();
			}
			currentPart += c;
			inExponent = false;
		} else if (c == '^') {
			currentPart += c;
			inExponent = true;
		} else if (isalpha(c)) {
			if (!currentPart.empty() && !inExponent) {
				parts.push_back(currentPart);
				currentPart.clear();
			}
			currentPart += c;
			inExponent = false;
		} else if (c == '*') {
			if (!currentPart.empty()) {
				parts.push_back(currentPart);
				currentPart.clear();
			}
			inExponent = false;
		}
	}
	if (!currentPart.empty())
		parts.push_back(currentPart);

	return parts;
}	


static void	msg_exit(std::string msg) {
	std::cout << msg << std::endl;
	exit(1);
}

static double myPow(double base, int exp) {
	if (exp == 0)
		return 1;

	double result = 1;

	for (int i = 0; i < exp; ++i)
		result *= base;

	return result;
}
