#include "computor.hpp"


void checkComposition(std::string &equation) {
	std::string::size_type pos = equation.find_first_not_of("1234567890xX.*^+-= \t");

	if (pos != std::string::npos)
		errorExit("input error: invalid character '" + std::string(1, equation[pos]) + "'");
}


void	normalizeX(std::string &equation) {
	std::replace(equation.begin(), equation.end(), 'x', 'X');
}


void	splitEquation(std::string &equation, std::string &left_polynom, std::string &right_polynom) {
	size_t equalSignCount = std::count(equation.begin(), equation.end(), '=');

	if (equalSignCount != 1)
		errorExit("input error: equation must contain exactly one '=' sign.");

	size_t equalPos = equation.find('=');

	left_polynom = equation.substr(0, equalPos);
	right_polynom = equation.substr(equalPos + 1);
}


void checkSyntax(std::string equation) {
	equation.erase(std::remove(equation.begin(), equation.end(), ' '), equation.end());
	equation.erase(std::remove(equation.begin(), equation.end(), '\t'), equation.end());

	for (size_t i = 1; i < equation.size() - 1; ++i)
		if (equation[i] == '.' && (!isdigit(equation[i - 1]) || !isdigit(equation[i + 1])))
			errorExit("input error: invalid position of '.'");

	if (equation.empty() || (!isdigit(equation[0]) && equation[0] != '-'))
		errorExit("input error: the first character must be a digit or '-'");

	const char* forbidden_combinations[] = {
		"*+", "+*", "*-", "-*", "^+", "+^", "^-", "-^", "*^", "^*", "^^",
		"/*", "*/", "/*", "*/", "/*", "*/*", "*//", "//*", "//"
	};
	for (size_t i = 0; i < sizeof(forbidden_combinations) / sizeof(forbidden_combinations[0]); ++i)
		if (equation.find(forbidden_combinations[i]) != std::string::npos)
			errorExit("input error: invalid operator combination '" + std::string(forbidden_combinations[i]) + "'");

	if (equation.find("***") != std::string::npos)
		errorExit("input error: more than two '*' consecutively");

	for (size_t i = 1; i < equation.size(); ++i)
		if ((equation[i] == 'X' || equation[i] == 'x') && (equation[i - 1] == '^' || (i > 1 && equation[i - 1] == '*' && equation[i - 2] == '*')))
			errorExit("input error: 'X' cannot follow '^' or '**'");

	std::string validCharacters = "0123456789xX";
	for (size_t i = 1; i < equation.size() - 1; ++i) {
		if (strchr("+-*/^", equation[i])) {
			bool beforeIsValid = validCharacters.find(equation[i - 1]) != std::string::npos || strchr("+-*/^", equation[i - 1]);
			bool afterIsValid = validCharacters.find(equation[i + 1]) != std::string::npos || strchr("+-*/^", equation[i + 1]);
			if (!beforeIsValid || !afterIsValid)
				errorExit("input error: operators must be surrounded by numbers or 'X'");
		}
	}

	for (size_t i = 0; i < equation.size(); ++i) {
		if (strchr("+-*/^", equation[i])) {
			size_t j = i;
			while (j < equation.size() && strchr("+-*/^", equation[j]))
				j++;
			if (j == i || j == equation.size() || (j - i > 1 && !isdigit(equation[j]) && equation[j] != 'x' && equation[j] != 'X'))
				errorExit("input error: invalid sequence of operators");
			i = j - 1;
		}
	}
}


bool isBothSpace(char lhs, char rhs) {
	return lhs == ' ' && rhs == ' ';
}

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


void reduceOperators(std::string &equation) {
	std::string reducedEquation;
	char lastOperator = '\0';

	for (size_t i = 0; i < equation.size(); ++i) {
		char c = equation[i];

		if (c == '+' || c == '-') {
			if (lastOperator == '\0')
				lastOperator = c;
			else {
				if (lastOperator == '+' && c == '+')
					lastOperator = '+';
				else if (lastOperator == '-' && c == '-')
					lastOperator = '+';
				else if ((lastOperator == '+' && c == '-') || (lastOperator == '-' && c == '+'))
					lastOperator = '-';
			}
		} else {
			if (lastOperator != '\0') {
				reducedEquation += lastOperator;
				lastOperator = '\0';
			}
			reducedEquation += c;
		}
	}
	if (lastOperator != '\0')
		reducedEquation += lastOperator;

	equation = reducedEquation;
}


void	splitPolynom(std::string &str_polynom, std::vector<std::string> &vec_polynom) {
	std::string currentMonome;
	bool isNegative = false;

	for (size_t i = 0; i < str_polynom.size(); ++i) {
		char c = str_polynom[i];

		if (c == '+' || c == '-') {
			if (!currentMonome.empty()) {
				if (isNegative)
					vec_polynom.push_back("-" + currentMonome);
				else
					vec_polynom.push_back(currentMonome);
				currentMonome.clear();
			}
			isNegative = (c == '-');
		} else
			currentMonome += c;
	}
	if (!currentMonome.empty()) {
		if (isNegative)
			vec_polynom.push_back("-" + currentMonome);
		else
			vec_polynom.push_back(currentMonome);
	}
}


std::vector<std::string> splitAndValidatePower(const std::string &input) {
    std::vector<std::string> parts;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, '^')) {
        if (!parts.empty())
            if (item.find('.') != std::string::npos) 
                errorExit("input error: float used as exponent");
        parts.push_back(item);
    }
    return parts;
}

void resolvePowerGroups(std::string &term) {
    std::vector<std::string> parts = splitAndValidatePower(term);

    if (parts.empty())
        return;

    if (parts[0] == "X" || parts[0] == "x") {
        int totalExponent = 1;
        for (size_t i = 1; i < parts.size(); ++i)
            totalExponent *= std::stoi(parts[i]);
        term = "X^" + std::to_string(totalExponent);
    } else {
        double base = std::stod(parts[0]);
        for (size_t i = 1; i < parts.size(); ++i)
            base = myPow(base, std::stoi(parts[i]));
        term = std::to_string(base);
    }
}

void resolveTerm(std::string &term) {
    std::vector<std::string> elements;
    std::stringstream ss(term);
    std::string item;

    while (ss >> item) {
        std::string cleanItem;
        for (size_t i = 0; i < item.size(); ++i)
            if (item[i] != '*')
                cleanItem += item[i];
        if (!cleanItem.empty())
            elements.push_back(cleanItem);
    }

    for (size_t i = 0; i < elements.size(); ++i)
        if (elements[i].find('^') != std::string::npos)
            resolvePowerGroups(elements[i]);

    double coefficient = 1.0;
    int totalExponent = 0;

    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i][0] == 'X') {
            if (elements[i].size() > 1)
                totalExponent += std::atoi(elements[i].substr(2).c_str());
            else
                totalExponent += 1;
        } else
            coefficient *= std::atof(elements[i].c_str());
    }

    std::ostringstream result;
    result << coefficient;
    if (totalExponent != 0)
        result << "X^" << totalExponent;
    term = result.str();
}


void resolvePolynom(std::vector<std::string> str_polynom, std::map<size_t, double> &polynom) {
    for (size_t i = 0; i < str_polynom.size(); ++i) {
        resolveTerm(str_polynom[i]);

        std::string term = str_polynom[i];
        size_t pos = term.find("X^");
        if (pos != std::string::npos) {
            double coefficient = std::atof(term.substr(0, pos).c_str());
            size_t exponent = std::atoi(term.substr(pos + 2).c_str());
            polynom[exponent] += coefficient;
        } else
            polynom[0] += std::atof(term.c_str());
    }
}


void	parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom) {
	checkComposition(equation);
	normalizeX(equation);

	std::string	s_left_polynom, s_right_polynom;
	splitEquation(equation, s_left_polynom, s_right_polynom);

	checkSyntax(s_left_polynom);
	checkSyntax(s_right_polynom);

	spacePolynom(s_left_polynom);
	spacePolynom(s_right_polynom);

	reduceOperators(s_left_polynom);
	reduceOperators(s_right_polynom);

	std::vector<std::string> v_left_polynom, v_right_polynom;
	splitPolynom(s_left_polynom, v_left_polynom);
	splitPolynom(s_right_polynom, v_right_polynom);

	resolvePolynom(v_left_polynom, left_polynom);
	resolvePolynom(v_right_polynom, right_polynom);
}
