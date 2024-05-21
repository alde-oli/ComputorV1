#include "computor.hpp"

static void						removeGarbage(std::string &str);
static std::vector<std::string>	splitPolynomial(const std::string& poly);
static void						resolveTerm(std::string& term, std::map<size_t, double>& polynom);
static void						validateTerm(std::string& term, bool &is_negative);
static double					computePower(const std::string& power_group);
static std::vector<std::string>	splitTerm(const std::string& term);
static std::vector<std::string>	splitPolynomial(const std::string& polynom);


void	parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom) {
	removeGarbage(equation);

	size_t						invalid_pos;
	if ((invalid_pos = equation.find_first_not_of("0123456789xX.*^+-=")) != std::string::npos)
		errorExit("input error: invalid token: \'" + std::string(1, equation[invalid_pos]) + "\'");

	size_t						pos = equation.find('=');
	if (pos == std::string::npos)
		errorExit("input error: missing token: \'=\'");

	std::string					left_str = equation.substr(0, pos);
	std::string					right_str = equation.substr(pos + 1);

	std::vector<std::string>	left_terms_str = splitPolynomial(left_str);
	std::vector<std::string>	right_terms_str = splitPolynomial(right_str);

	for (size_t i = 0; i < left_terms_str.size(); i++)
		resolveTerm(left_terms_str[i], left_polynom);

	for (size_t i = 0; i < right_terms_str.size(); i++)
		resolveTerm(right_terms_str[i], right_polynom);
}


static void	removeGarbage(std::string &str) {
	size_t	pos;
	while ((pos = str.find_first_of(" \t\n\r\x0B")) != std::string::npos)
			str.erase(pos, 1);
}


static std::vector<std::string>	splitPolynomial(const std::string& polynom) {
	std::vector<std::string>	terms;
	std::string					term;
	int							start = 0;

	for (size_t i = 0; i < polynom.length(); i++) {
		if ((polynom[i] == '+' || polynom[i] == '-') && ((i + 1 == polynom.length()) || !(polynom[i + 1] >= '0' && polynom[i + 1] <= '9')))
			errorExit("input error: sign " + std::string(&polynom[i], 1) + " not followed by an expression");
		if ((polynom[i] == '+' || polynom[i] == '-') && i > 0) {
			term = polynom.substr(start, i - start);
			if (term[0] == '+')
				term = term.substr(1);
			terms.push_back(term);
			start = i;
		}
	}
	term = polynom.substr(start);
	if (term[0] == '+')
		term = term.substr(1);
	terms.push_back(term);
	return terms;
}


static void	resolveTerm(std::string& term, std::map<size_t, double>& polynom) {
	bool						is_negative = false;
	
	validateTerm(term, is_negative);

	std::vector<std::string>	parts = splitTerm(term);
	double						coefficient = 1.0;
	size_t						exponent = 0;

	for (std::vector<std::string>::iterator part = parts.begin(); part != parts.end(); part++) {
		if ((*part).find('X') != std::string::npos) {
			size_t expPos = (*part).find('^');
			if (expPos != std::string::npos) {
				std::string expPart = (*part).substr(expPos + 1);
				exponent += static_cast<size_t>(computePower(expPart));
			} else
				exponent += 1;
		} else
			coefficient *= computePower((*part));
	}
	if (is_negative)
		coefficient = -coefficient;

	polynom[exponent] += coefficient;
}


static void	validateTerm(std::string& term, bool &is_negative) {;
	size_t		x_pos;

	if (!term.length())
		errorExit("input error: consecutive \'+\' operators");

	while ((x_pos = term.find('x')) != std::string::npos)
		term[x_pos] = 'X';
	if (term[0] == '-') {
		is_negative = true;
		term = term.substr(1);
	}

	if (term[0] == '*' || term[0] == '^' || term[term.length() - 1] == '*' || term[term.length() - 1] == '^')
		errorExit("input error: unexpected operator in term " + term);
	
	for (size_t i = 0; i < term.length() - 1; ++i) {
		if (term[i] == '^' && term[i + 1] == 'X')
			errorExit("input error: variable used as exponent in term " + term);
		if ((term[i] == '*' || term[i] == '^') && (term[i + 1] == '*' || term[i + 1] == '^'))
			errorExit("input error: consecutive operators in term " + term);
	}

}


static double computePower(const std::string& power_group) {
    std::vector<double> numbers;
    std::string number;
    bool isDecimal = false;

    for (size_t i = 0; i < power_group.size(); ++i) {
        if (isdigit(power_group[i]) || (power_group[i] == '.' && !isDecimal)) {
            if (power_group[i] == '.')
                isDecimal = true;
            number += power_group[i];
        } else if (power_group[i] == '^') {
            if (!number.empty()) {
                numbers.push_back(std::atof(number.c_str()));
                number.clear();
                isDecimal = false;
            }
        } else
            errorExit("input error: invalid character in power group");
    }
    if (!number.empty())
        numbers.push_back(std::atof(number.c_str()));

    double result = numbers.back();
    for (int i = numbers.size() - 2; i >= 0; --i)
        result = myPow(numbers[i], result);

    return result;
}



static std::vector<std::string> splitTerm(const std::string& term) {
    std::vector<std::string>	parts;
    std::string					current_part;
    bool						in_exponent = false;
    bool						isDecimal = false;

    for (size_t i = 0; i < term.length(); ++i) {
        char c = term[i];

        if (isdigit(c) || (c == '.' && !isDecimal)) {
            if (c == '.')
                isDecimal = true;
            if (!in_exponent && !current_part.empty() && !isdigit(current_part.back()) && current_part.back() != '^') {
                parts.push_back(current_part);
                current_part.clear();
                isDecimal = false;
            }
            current_part += c;
            in_exponent = false;
        } else if (c == '^') {
            current_part += c;
            in_exponent = true;
            isDecimal = false;
        } else if (isalpha(c)) {
            if (!current_part.empty() && !in_exponent) {
                parts.push_back(current_part);
                current_part.clear();
                isDecimal = false;
            }
            current_part += c;
            in_exponent = false;
        } else if (c == '*') {
            if (!current_part.empty()) {
                parts.push_back(current_part);
                current_part.clear();
                isDecimal = false;
            }
            in_exponent = false;
        } else
            errorExit("input error: invalid character in term");
    }
    if (!current_part.empty())
        parts.push_back(current_part);

    return parts;
}

