#include "computor.hpp"


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