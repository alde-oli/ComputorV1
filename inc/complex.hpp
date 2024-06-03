#pragma once

#include "computor.hpp"



class Complex {
	public:
		Complex();
		Complex(const Complex &other);
		Complex(double real, double imaginary);
		~Complex();


		Complex					&operator=(const Complex &other);
		Complex					&operator=(double x);

		Complex					operator+(const Complex &other) const;
		Complex					operator+(const double x) const;

		Complex					operator-(const Complex &other) const;
		Complex 				operator-(const double x) const;

		Complex					operator*(const Complex &other) const;
		Complex 				operator*(const double x) const;

		Complex					operator/(const Complex &other) const;
		Complex 				operator/(const double x) const;

		friend std::ostream&	operator<<(std::ostream& os, const Complex& complex);


		double					norm() const;
		Complex					conjugate() const;


		double					getReal() const;
		double					getImaginary() const;


	private:
		double					_real;
		double					_imaginary;
};
