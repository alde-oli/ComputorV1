#pragma once

#include "computor.hpp"

class Complex {
	public:
		Complex();
		Complex(const Complex &other);
		Complex(double real, double imaginary);


		Complex	&operator=(const Complex &other);

		Complex	operator+(const Complex &other);
		Complex operator+(const double x);

		Complex operator-(const Complex &other);
		Complex operator-(const double x);

		Complex operator*(const Complex &other);
		Complex operator*(const double x);

		Complex operator/(const Complex &other);
		Complex operator/(const double x);


		double	norm() const;
		Complex	conjugate() const;


		double	getReal() const;
		double	getImaginary() const;


	private:
		double	_real;
		double	_imaginary;
};