#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>

int		computor(std::string input);

void	parseEquation(std::string &equation, std::map<size_t, double> leftPolynom, std::map<size_t, double> rightPolynom);

void	reduceEquation(std::map<size_t, double> leftPolynom, std::map<size_t, double> rightPolynom);

void	solver0(std::map<size_t, double> polynom);
void	solver1(std::map<size_t, double> polynom);
void	solver2(std::map<size_t, double> polynom);
void	solver3(std::map<size_t, double> polynom);
void	solver4(std::map<size_t, double> polynom);
