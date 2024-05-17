#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include "Complex.hpp"


#define NROOT_TOLERANCE 1e-6
#define TRIGO_RECURSION 200


void	computor(std::string input);

void	parseEquation(std::string &equation, std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom);

void	reduceEquation(std::map<size_t, double> &left_polynom, std::map<size_t, double> &right_polynom);

void	solver0(std::map<size_t, double> &polynom);
void	solver1(std::map<size_t, double> &polynom);
void	solver2(std::map<size_t, double> &polynom);
void	solver3(std::map<size_t, double> &polynom);
void	solver4(std::map<size_t, double> &polynom);

double	myPow(double x, int exp);
double	mynRoot(double x, int n);
int		myFactorial(unsigned int x);
double	myCos(double x);
double	mySin(double x);

void	errorExit(std::string msg);
