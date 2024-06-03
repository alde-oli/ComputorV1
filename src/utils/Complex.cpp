#include "computor.hpp"
#include "Complex.hpp"


////////////////////////////////////
//--Constructors ans destructor--///
////////////////////////////////////
Complex::Complex() 
	: _real(0), _imaginary(0) {
}

Complex::Complex(const Complex &other) {
	*this = other;
}

Complex::Complex(double real, double imaginary) 
	: _real(real), _imaginary(imaginary) {
}

Complex::~Complex() {
}

//////////////////////////
//--Operators overload--//
//////////////////////////
Complex	&Complex::operator=(const Complex &other) {
	_real = other.getReal();
	_imaginary = other.getImaginary();

	return *this;
}

Complex	&Complex::operator=(double x) {
	_real = x;
	_imaginary = 0;

	return *this;
}


Complex	Complex::operator+(const Complex &other) const {
	return Complex(_real + other.getReal(), _imaginary + other.getImaginary());
}

Complex Complex::operator+(const double x) const {
	return Complex(_real + x, _imaginary);
}


Complex Complex::operator-(const Complex &other) const {
	return Complex(_real - other.getReal(), _imaginary - other.getImaginary());
}

Complex Complex::operator-(const double x) const {
	return Complex(_real - x, _imaginary);
}


Complex Complex::operator*(const Complex &other) const {
	double	new_real = _real * other.getReal() - _imaginary * other.getImaginary();
	double	new_imaginary = _real * other.getImaginary() + _imaginary * other.getReal();

	return Complex(new_real, new_imaginary);
}

Complex Complex::operator*(const double x) const {
	return Complex(_real * x, _imaginary * x);
}


Complex Complex::operator/(const Complex &other) const {
	double denom = myPow(other.getReal(), 2) + myPow(other.getImaginary(), 2);
	if (denom == 0)
		errorExit("Complex error: division by 0");
	double temp_real = (_real * other.getReal() + _imaginary * other.getImaginary()) / denom;
	double temp_imaginary = (_imaginary * other.getReal() - _real * other.getImaginary()) / denom;
	return Complex(temp_real, temp_imaginary);
}


Complex Complex::operator/(const double x) const {
	return Complex(_real / x, _imaginary / x);
}

std::ostream& operator<<(std::ostream& os, const Complex& complex) {
	if (complex._imaginary) {
		if (complex._imaginary < 0)
			os << complex._real << " - " << complex._imaginary * -1 << "i";
		else
			os << complex._real << " + " << complex._imaginary << "i";
	} else
		os << complex._real;
	return os;
}

///////////////////////////
//--Additionnal methods--//
///////////////////////////
double	Complex::norm() const {
	return mynRoot((myPow(_real, 2) + myPow(_imaginary, 2)), 2);
}

Complex	Complex::conjugate() const {
	return Complex(_real, -_imaginary);
}

///////////////////////////
//--Getters and setters--//
///////////////////////////
double	Complex::getReal() const {
	return _real;
}

double	Complex::getImaginary() const {
	return _imaginary;
}
