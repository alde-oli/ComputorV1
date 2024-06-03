#pragma once

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include "Complex.hpp"
#include "verbose.hpp"


#define PI 3.14159265358979323846
#define NROOT_TOLERANCE 1e-10
#define TRIGO_RECURSION 200


#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define VIOLET "\033[38;2;128;0;128m"
#define PINK "\033[38;2;255;192;203m"
#define GOLD "\033[38;2;255;215;0m"
#define CYAN "\033[36m"
#define RESET "\033[0m"


// computor
void		computor(std::string input);
void		reduceEquation(std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom);

// parser
void		parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom);
void		checkComposition(const std::string &equation);
void		normalizeX(std::string &equation);
void		splitEquation(std::string &equation, std::string &left_polynom, std::string &right_polynom);
void		checkSyntax(const std::string &equation);
void		spacePolynom(std::string &equation);
void		reduceOperators(std::string &equation);
void		splitPolynom(std::string &str_polynom, std::vector<std::string> &vec_polynom);
void		resolvePolynom(std::vector<std::string> str_polynom, std::map<size_t, double> &polynom);

double		strToDouble(const std::string& str);
size_t		strToSizeT(const std::string& str);
std::string	doubleToStr(double n);
std::string	sizeTToStr(size_t n);

char		nextNonspaceValue(const std::string &equation, int i);
int			nextNonspacePos(const std::string &equation, int i);

// solvers
void		solver0(std::map<size_t, double> &polynom);
void		solver1(std::map<size_t, double> &polynom);
void		solver2(std::map<size_t, double> &polynom);
void		solver3(std::map<size_t, double> &polynom);

// utils
double		myPow(double x, int exp);
double		mynRoot(double x, int n);
int			myFactorial(unsigned int x);
double		myCos(double x);
double		mySin(double x);
double		myArcCos(double x);
double		myArcSin(double x);

void		pointError(const std::string &equation, int i, const std::string &error_msg);
void		errorExit(const std::string msg);
